#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectionData.h"
#include<QSqlError>
#include<vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createConnection();

    mycharge =new chargeDia(this);
    connect(ui->pushButton,&QPushButton::clicked,mycharge,&chargeDia::open);

    mycount= new countdia(this);
    connect(ui->pushButton_2,&QPushButton::clicked,mycount,&countdia::open);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_2_clicked()
{
    std::vector<QMap<QString, QString>> vectorOfMaps;
    vectorOfMaps.push_back(countFee("Internal","wechat"));
    vectorOfMaps.push_back(countFee("Internal","alipay"));
    vectorOfMaps.push_back(countFee("Internal","cash"));
    vectorOfMaps.push_back(countFee("Visitor","wechat"));
    vectorOfMaps.push_back(countFee("Visitor","alipay"));
    vectorOfMaps.push_back(countFee("Visitor","cash"));
    mycount->processData(vectorOfMaps);
}

QMap<QString, QString> MainWindow::countFee(QString type,QString payw){
    QSqlDatabase db= QSqlDatabase::database("DISK");
    QSqlQuery query(db);
    QString numberOfVehicles;
    QString totalAmount;
    QString queryStr = QString("SELECT COUNT(*) AS NumberOfVehicles, IFNULL(SUM(FeeAmount), 0) AS TotalAmount FROM ParkingFee WHERE PayWay = '%1' AND VehicleType = '%2' AND DATE(ExitTime) = CURDATE();").arg(payw).arg(type);
    query.exec(queryStr);
    if (query.next()){
        numberOfVehicles = query.value("NumberOfVehicles").toString();
        totalAmount = query.value("TotalAmount").toString();
    } else {
        // 查询执行失败，获取错误信息
        QSqlError error = query.lastError();
        qDebug() << "MySQL Error: " << error.text();
    }
    QMap<QString, QString> resultMap;
    resultMap[numberOfVehicles] = totalAmount;
    return resultMap;
}

