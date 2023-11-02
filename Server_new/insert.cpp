#include "insert.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include<QThread>
#include <QSqlError>
#include <QTimer>

Insert::Insert()
{
    QTimer timer;
    timer.setInterval(10*60*1000);
    QObject::connect(&timer, &QTimer::timeout,
                     [=] () {
                         QSqlDatabase db = QSqlDatabase::database("DISK");
                         QSqlQuery query(db);
                         QStringList::ConstIterator it;
                         for(it=insertList.constBegin();it!=insertList.constEnd();it++){
                             QString item=*it;
                             qDebug()<<item;
                             query.exec(item);
                         }
                     });
    timer.start();
}

void Insert::updateList(const QString& param){
    QMutexLocker locker(&mutex);
    insertList.append(param);
}
