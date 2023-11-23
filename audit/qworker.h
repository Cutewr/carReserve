#ifndef QWORKER_H
#define QWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>

class QWorker : public QObject
{
    Q_OBJECT
public:
    explicit QWorker(QObject *parent = nullptr);
    ~QWorker();

signals:
    void newData(QByteArray data);    // 将本类内的私有数据通过该信号发射出去，供外部使用

public slots:
    void init();         // 一些必要的初始化操作写在此函数内
    void doWork();       // 一些耗时操作写在此函数内
    void writeData(const char* buf, qint64 len);  // 供外部使用的操作接口
};

#endif // QWORKER_H
