#include "dialog.h"
#include "server.h"
#include "serverthread.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    m_dialog = dynamic_cast<Dialog *>(parent);
}

Server::~Server()
{

}

void Server::incomingConnection(qintptr sockDesc)
{
    m_socketList.append(sockDesc);
    serverThread *thread = new serverThread(sockDesc);
    m_dialog->showConnection(sockDesc);

    connect(thread, SIGNAL(disconnectTCP(int)), m_dialog, SLOT(showDisconnection(int)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(dataReady(const QString&, const QByteArray&)),m_dialog, SLOT(recvData(const QString&, const QByteArray&)));
    connect(m_dialog, SIGNAL(sendData(int, const QByteArray&)),thread, SLOT(sendDataSlot(int, const QByteArray&)));
    qDebug()<<m_socketList;
    thread->start();
}

void Server::startInsert(QStringList insertlist){
    QSqlDatabase db = QSqlDatabase::database("DISK");
    QSqlQuery query(db);
    QStringList::ConstIterator it;
    for(it=insertList.constBegin();it!=insertList.constEnd();it++){
        QString item=*it;
        qDebug()<<item;
        query.exec(item);
    }
}

