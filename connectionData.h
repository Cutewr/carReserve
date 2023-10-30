#ifndef CONNECTIONDATA_H
#define CONNECTIONDATA_H

#endif // CONNECTIONDATA_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

static bool createConnection(){
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","MEMORY");
    db.setDatabaseName(":memory:");
    if(!db.open())
    {
        QMessageBox::critical(0,"Cannot open database","Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
    query.exec("create table reserveCar(no INTEGER PRIMARY KEY AUTOINCREMENT,car_id text,visitor_id varchar(20),intime datetime,outtime datetime,fee int)");
    //当前进校的车辆
    QString createCar=QString("CREATE TABLE CurrentAccess (VehicleID VARCHAR(20) PRIMARY KEY,EntryDoorID INT,ExitDoorID INT,EntryTime DATETIME,ExitTime DATETIME NULL)");
    query.exec(createCar);
    QSqlQuery query1(db1);
    query1.exec("select date,vehicle_id,visitor_id from reserve where date(date) in (CURDATE(), CURDATE() + INTERVAL 1 DAY, CURDATE() + INTERVAL 2 DAY);");
    for(int i = 0; query1.next(); i++)
    {
        QString dateinfo=query1.value(0).toString();
        QString vehicle_id=query1.value(1).toString();
        QString visitor_id=query1.value(2).toString();
        QString in=QString("insert into reserveCar(car_id,visitor_id,intime)values('%1','%2','%3');").arg(vehicle_id).arg(visitor_id).arg(dateinfo);
        query.exec(in);
    }

    //预约信息表
    //query.exec("select * from reserveCar");
    //query.exec("create table reserveM(reserve_id integer primary key autoincrement,staff_no varchar(10),DT date ,way varchar(20),cause varchar(20),vehicle_id varchar(20),visitor_id varchar(20))");
    return true;
}
