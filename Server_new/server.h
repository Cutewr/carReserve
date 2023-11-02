#ifndef SERVER_H
#define SERVER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include<QMutex>

#include <QTcpServer>

class Dialog;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = Q_NULLPTR);
    ~Server();

private:
    void incomingConnection(qintptr sockDesc);

private:
    Dialog *m_dialog;
    QList<int> m_socketList;

public slots:
};

#endif // SERVER_H
