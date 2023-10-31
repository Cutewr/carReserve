#include "serverthread.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

serverThread::serverThread(int sockDesc, QObject *parent) :
    QThread(parent),
    m_sockDesc(sockDesc)
{

}

serverThread::~serverThread()
{
    m_socket->close();
}

void serverThread::run(void)
{
    m_socket = new MySocket(m_sockDesc);

    if (!m_socket->setSocketDescriptor(m_sockDesc)) {
        return ;
    }
    connect(m_socket, &MySocket::disconnected, this, &serverThread::disconnectToHost);
    connect(m_socket, SIGNAL(dataReady(const QString&, const QByteArray&)),this, SLOT(recvDataSlot(const QString&, const QByteArray&)));
    connect(this, SIGNAL(sendData(int, const QByteArray&)),m_socket, SLOT(sendData(int, const QByteArray&)));
    connect(this, SIGNAL(sendInsert(const QByteArray&)),server, SLOT(sendData(int, const QByteArray&)));
    this->exec();
}

void serverThread::sendDataSlot(int sockDesc, const QByteArray &data)
{
    if (data.isEmpty()) {
        return ;
    }
    emit sendData(sockDesc, data);
}

void serverThread::recvDataSlot(const QString &ip, const QByteArray &data)
{
    qDebug()<<QThread::currentThreadId();
    emit dataReady(ip, data);
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data);
    QJsonObject jsonObject1=jsonDoc.object();
    QJsonArray dataArray=jsonObject1["dataArray"].toArray();
    QJsonObject jsonObject=jsonObject1["data"].toObject();

    QString staff_name=jsonObject["name"].toString();
    QString staff_no=jsonObject["no"].toString();
    QString redate=jsonObject["redate"].toString();
    QString way=jsonObject["way"].toString();
    QString cause=jsonObject["cause"].toString();
    QString vehicle_id=jsonObject["vehicle_id"].toString();
    QString id1=jsonObject["visitor_id"].toString();

    QSqlDatabase dbM = QSqlDatabase::database("MEMORY");
    QSqlQuery queryM(dbM);

    //校内人员信息是否正确
    QString selM=QString("select staff_name from staffM where staff_no='%1';").arg(staff_no);
    queryM.exec(selM);
    if(!queryM.next()||queryM.value(0).toString()!=staff_name){
        emit sendData(m_sockDesc, "staffNo");
        return;
    }
    else{
        emit sendData(m_sockDesc, "staffYes");
        emit sendInsert("DataYes");
    }

    QString reserve_insert=QString("insert into reserve(staff_no,date,way,cause,vehicle_id,visitor_id) values('%1','%2','%3','%4','%5','%6');").arg(staff_no).arg(redate).arg(way).arg(cause).arg(vehicle_id).arg(id1);
    insertList.append(reserve_insert);

    QThread insertThread;
    this->moveToThread(&insertThread);
    QTimer timer;
    timer.setInterval(10*60*1000);
    QObject::connect(&timer,&QTimer::timeout,this,SLOT(doInsert(QStringList &insertList)));
    insertThread.start();
    timer.start();
}

void serverThread::disconnectToHost(void)
{
    emit disconnectTCP(m_sockDesc);     //server->dialog修改页面
    m_socket->disconnectFromHost();
    this->quit();
}

void serverThread::doInsert(QStringList &insertList)
{
    QSqlDatabase db = QSqlDatabase::database("DISK");
    QSqlQuery query(db);
    QStringList::ConstIterator it;
    for(it=insertList.constBegin();it!=insertList.constEnd();it++){
        QString item=*it;
        qDebug()<<item;
        if(query.exec(item)){
            emit sendData(m_sockDesc, "dataYes");
        }
        else{
            qDebug()<<query.lastError().text();
            return;
        }
    }
}
