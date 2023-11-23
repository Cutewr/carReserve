#ifndef CONNECTION_H
#define CONNECTION_H

#endif // CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

static bool createConnection(){
    const QString Name="DISK";
        QSqlDatabase db1 = QSqlDatabase::addDatabase("QMYSQL","DISK");
        db1.setHostName("localhost");
        db1.setPort(3306);
        db1.setDatabaseName("carReserve");
        db1.setUserName("root");
        db1.setPassword("wr123456");
        if(!db1.open())
        {
            QMessageBox::critical(0,"Cannot open database","Unable to establish a database connection.",QMessageBox::Cancel);
            return false;
        }
    return true;
}
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","MEMORY");
//    db.setDatabaseName(":memory:");
//    if(!db.open())
//    {
//        QMessageBox::critical(0,"Cannot open database","Unable to establish a database connection.",QMessageBox::Cancel);
//        return false;
//    }
//    QSqlQuery query(db);
//    query.exec("create table staffM(staff_no vachar(10) primary key,staff_name vachar(20),campus varchar(10),staff_id vachar(20))");
//    QSqlQuery query1(db1);
//    query1.exec("select * from staff;");
//    for(int i = 0; query1.next(); i++)
//    {
//        QString name=query1.value(0).toString();
//        QString no=query1.value(1).toString();
//        QString school=query1.value(2).toString();
//        QString id=query1.value(3).toString();
//        QString in=QString("insert into staffM(staff_no,staff_name,campus,staff_id) values('%1','%2','%3','%4');").arg(no).arg(name).arg(school).arg(id);
//        query.exec(in);
//    }
//    //预约信息表
//    query.exec("create table reserveM(reserve_id integer primary key autoincrement,staff_no varchar(10),DT date ,way varchar(20),cause varchar(20),vehicle_id varchar(20),visitor_id varchar(20))");


