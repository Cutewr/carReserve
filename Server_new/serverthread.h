#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <dialog.h>
#include "mysocket.h"
#include "server.h"
#include "insert.h"

class Socket;

class serverThread : public QThread
{
    Q_OBJECT
public:
    serverThread(int sockDesc, QObject *parent = Q_NULLPTR);
     serverThread(Dialog* dialog) : dialogObject(dialog) {}
    ~serverThread();

private:
    void run(void);

public slots:
    void sendDataSlot(int sockDesc, const QByteArray &data);

signals:
    void dataReady(const QString &ip, const QByteArray &data);
    void sendData(int sockDesc, const QByteArray &data);
    void sendInsert(const QString& param);
    void disconnectTCP(int sockDesc);

private slots:   
    void recvDataSlot(const QString &ip, const QByteArray &data);
    void disconnectToHost(void);


private:
    MySocket *m_socket;
    Server *server;
    int m_sockDesc;
    Insert *m_insert;
    Dialog* dialogObject;
};

#endif // SERVERTHREAD_H
