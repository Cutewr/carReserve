#ifndef INSERT_H
#define INSERT_H

#include <QMutex>
#include <QStringList>
#include<QObject>


class Insert :public QObject
{
    Q_OBJECT
public:
    Insert();
    QStringList insertList;
    QMutex mutex;
public slots:
    void updateList(const QString& param);
};

#endif // INSERT_H
