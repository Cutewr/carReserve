#include <QMessageBox>

#include "server.h"
#include "dialog.h"
#include "dataConnect.h"
#include "ui_dialog.h"
#include<QSqlError>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_timer(new QTimer(this)),
    m_server(new Server(this)),
    m_count(0)
{
    ui->setupUi(this);
    createConnection();

    setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);

    ui->btnStopLoop->setDisabled(true);
    ui->labelNum->setText(QString("%1").arg(m_count));

    m_server = new Server(this);
    m_server->listen(QHostAddress::Any, 8712);

    connect(ui->btnSend,        SIGNAL(clicked()),      this, SLOT(sendDataSlot()));
    connect(ui->btnClear,       SIGNAL(clicked()),      this, SLOT(clearData()));
    connect(m_timer,            SIGNAL(timeout()),      this, SLOT(startLoopSend()));
    connect(ui->btnStopLoop,    SIGNAL(clicked(bool)),  this, SLOT(stopLoopSend()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showConnection(int sockDesc)
{
    m_count++;
    ui->comboBoxObj->addItem(QString("%1").arg(sockDesc), sockDesc);
    ui->labelNum->setText(QString("%1").arg(m_count));
}

void Dialog::showDisconnection(int sockDesc)
{
    m_count--;

    /* refresh combobox */
    ui->comboBoxObj->clear();
    int index = ui->comboBoxObj->findData(sockDesc);

    ui->comboBoxObj->removeItem(index);

    /* change connect number while connection is disconnecting */
    ui->labelNum->setText(QString("%1").arg(m_count));
}

void Dialog::sendHexData(void)
{
    QString allData = ui->lineEditMsg->text();
    QByteArray data;

    QStringList list = allData.split(" ");
    for (const QString &hex : list) {
        data.append(static_cast<char>(hex.toInt(Q_NULLPTR, 16)));
    }
    emit sendData(ui->comboBoxObj->currentText().toInt(), data);
}

void Dialog::sendDataSlot(void)
{
    /* if send message is null return */
    if (ui->lineEditMsg->text().isEmpty()) {
        QMessageBox::information(Q_NULLPTR, QString("注意"), QString("发送内容不能为空！"), QMessageBox::Yes);
        return ;
    }

    if (ui->checkBoxLoop->isChecked()) {
        int time_period = ui->lineEditLoopTime->text().toInt();

        m_timer->setInterval(time_period);
        m_timer->start();

        ui->btnSend->setDisabled(true);
        ui->btnStopLoop->setDisabled(false);
        return;
    }

    /* whether send hex data */
    if (ui->checkBoxHex->isChecked()) {
        sendHexData();
    } else {
        /* send original data */
        emit sendData(ui->comboBoxObj->currentText().toInt(), ui->lineEditMsg->text().toLocal8Bit());
    }

    ui->lineEditMsg->setText("");
}

void Dialog::recvData(const QString &ip, const QByteArray &data)
{
    QString msg;

    /* add ip address string to displaying string */
    if (!ui->checkBoxHideIP->isChecked()) {
        msg += ip + QString(": ");
    }

    /* choose data format to display */
    if (ui->checkBoxHex->isChecked()) {
        QString dataString;
        for (int i = 0; i < data.size(); i++) {
            dataString += QString("0x%1 ").arg(static_cast<quint8>(data.at(i)), 2, 16, QChar('0'));
        }
        msg += dataString + "\n";
    } else {
        msg += QString::fromLocal8Bit(data) + "\n";
    }

    /* send back data */
    if (ui->checkBoxCycle->isChecked()) {
        emit sendData(ui->comboBoxObj->currentText().toInt(), data);
    }

    ui->textBrowser->append(msg);

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
    QSqlDatabase db = QSqlDatabase::database("DISK");
    QSqlQuery query(db);

    //校内人员信息是否正确
    QString selM=QString("select staff_name from staffM where staff_no='%1';").arg(staff_no);
    queryM.exec(selM);
    if(!queryM.next()||queryM.value(0).toString()!=staff_name){
        emit sendData(ui->comboBoxObj->currentText().toInt(), "staffNo");
        return;
    }
    else{
        emit sendData(ui->comboBoxObj->currentText().toInt(), "staffYes");
    }

    QString reserve_insert=QString("insert into reserve(staff_no,date,way,cause,vehicle_id,visitor_id) values('%1','%2','%3','%4','%5','%6');").arg(staff_no).arg(redate).arg(way).arg(cause).arg(vehicle_id).arg(id1);
    if(query.exec(reserve_insert)){
        emit sendData(ui->comboBoxObj->currentText().toInt(), "dataYes");
    }
    else{
        qDebug()<<query.lastError().text();
        return;
    }
//    QString reserve_insertM=QString("insert into reserveM(staff_no,DT,way,cause,vehicle_id,visitor_id) values('%1','%2','%3','%4','%5','%6');").arg(staff_no).arg(redate).arg(way).arg(cause).arg(vehicle_id).arg(id1);
//    queryM.exec(reserve_insertM);
//    QString selReserveM=QString("select * from reserveM");
//    queryM.exec(selReserveM);
//    while(queryM.next())
//    {
//        qDebug()<<queryM.value(0).toString()<<queryM.value(1).toString()<<queryM.value(2).toString()<<queryM.value(3).toString()<<queryM.value(4).toString()<<queryM.value(5).toString()<<queryM.value(6).toString();
//    }

}

void Dialog::clearData(void)
{
    ui->textBrowser->clear();
}

void Dialog::startLoopSend(void)
{
    if (ui->checkBoxHex->isChecked()) {
        sendHexData();
    } else {
        emit sendData(ui->comboBoxObj->currentText().toInt(), ui->lineEditMsg->text().toLocal8Bit());
    }
}

void Dialog::stopLoopSend(void)
{
    m_timer->stop();
    ui->btnSend->setDisabled(false);
    ui->btnStopLoop->setDisabled(true);
}
