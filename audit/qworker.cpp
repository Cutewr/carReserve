#include "qworker.h"

QWorker::QWorker(QObject *parent) : QObject(parent)
{
    qDebug() << __FUNCTION__ << "Thread ID:" << QThread::currentThreadId();
}

QWorker::~QWorker()
{
    qDebug() << __FUNCTION__ << "Thread ID:" << QThread::currentThreadId();
}

void QWorker::init()
{
    qDebug() << __FUNCTION__ << "Thread ID:" << QThread::currentThreadId();
}

void QWorker::doWork()
{
    static int count = 0;
    qDebug() << __FUNCTION__ << "Thread ID:" << QThread::currentThreadId() << ">>>" << count++;
}

void QWorker::writeData(const char* buf, qint64 len)
{
    qDebug() << __FUNCTION__ << "Thread ID:" << QThread::currentThreadId() << ">>>" << QByteArray(buf, len);
}
