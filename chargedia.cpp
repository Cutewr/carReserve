#include "chargedia.h"
#include "ui_chargedia.h"
#include "QDateTime"
#include "QPalette"
#include "QFont"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QInputDialog"
#include "QLineEdit"
#include <QDateTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>
#include <QSqlError>

chargeDia::chargeDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chargeDia)
{

    ui->setupUi(this);
    //测试
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, [&]() {
        bool ok;
        QString text = QInputDialog::getText(this, "Input Dialog", "Enter text:", QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
            // 用户点击了“确定”按钮，并输入了文本
            ui->label_14->setText(text);
            charge(text);
        } else {
            // 用户点击了“取消”按钮或未输入文本
            qDebug() << "Canceled or no input.";
        }
    });

    QStringList strList;
    strList<<"附中车"<<"家长返校车"<<"学生返校车"<<"登记收费车"<<"来访车"<<"接待票车"<<"内部车辆";
    ui->comboBox->addItems(strList);

    QStringList strList2;
    strList2<<"小型车"<<"载客汽车"<<"货车";
    ui->comboBox_2->addItems(strList2);

    //入校时间和出校时间
    QDateTime intime;
    intime.setDate(QDate(2023,9,9));
    intime.setTime(QTime(7,10));
    QDateTime outtime;
    outtime.setDate(QDate(2023,9,9));
    outtime.setTime(QTime(10,53));
    //   QDateTime intime=QDateTime::currentDateTime().addSecs(-3600);
    QString inTime=intime.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_15->setText(inTime);
    //    QDateTime outtime= QDateTime::currentDateTime();//获取系统当前的时间
    QString outTime = outtime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    ui->label_16->setText(outTime);

    //停了多长时间
    qint64 secondsDifference = intime.secsTo(outtime);
    // 计算小时、分钟和秒
    int hoursDifference = secondsDifference / 3600;
    int minutesDifference = secondsDifference / 60;
    int minutes = (secondsDifference % 3600) / 60;
    int seconds = secondsDifference % 60;
    qint64 daysDifference =intime.daysTo(outtime);
    QString parkTime=QString("%1小时%2分钟%3秒").arg(hoursDifference).arg(minutes).arg(seconds);
    ui->label_17->setText(parkTime);
    //车牌号

    int fee; //费用
    //判读是否是来访人员
    QString carid=ui->label_14->text();
    if(!isVisitor(carid)){
        fee=0;
        ui->comboBox->setCurrentText("内部车辆");
    }
    else{
        //校外人员收费
        ui->comboBox->setCurrentText("来访车");
        int inhour=intime.time().hour();
        int outhour=outtime.time().hour();

        if(inhour>=19 && outhour<=7 && daysDifference==1){
            fee=7;
        }
        else if(minutesDifference<=30){
            fee=0;
        }
        else if(hoursDifference>=1 && hoursDifference<=2){
            fee=3+hoursDifference*6;
        }
        else if(hoursDifference>=3 && hoursDifference<=5){
            fee=3+12+(hoursDifference-2)*9;
        }
    }
    QString feeAsString = QString::number(fee)+"元";
    qDebug()<<feeAsString;
    ui->label_21->setText(feeAsString);

    //字体显示不同
    QPalette palette;
    QFont ft;
    ft.setPointSize(20);
    palette.setColor(QPalette::WindowText,Qt::red);
    ui->label_14->setPalette(palette);
     ui->label_14->setFont(ft);
    ui->label_17->setPalette(palette);
      ui->label_17->setFont(ft);
    ui->label_21->setPalette(palette);
     ui->label_21->setFont(ft);

    //判断是否同门进出
    QString inDoor=ui->label_19->text();
    QString outDoor=ui->label_20->text();
     if(inDoor==outDoor){
         ui->label_18->setText("同门进出");
     }
     else{
         ui->label_18->setText("异门进出");
     }
}

chargeDia::~chargeDia()
{
    delete ui;
}

void chargeDia::on_pushButton_6_clicked()
{
    this->close();
}


void chargeDia::on_pushButton_clicked()
{
    detail1 = new chargeDetail(this);
    detail1->sendData(ui->label_17->text(),ui->label_21->text()); //直接调用public函数将本页面中lineEdit的数据传递过去
    QString carid=ui->label_14->text();
    //判读是否是来访人员
    if(!isVisitor(carid)){
         detail1->isStaff();
    }
    detail1->setModal(false);
    detail1->show();
    m_mask=new QHMaskWidget(this);
    // 嵌入窗口.
    m_mask->addEmbeddedWindow(detail1);
    m_mask->show();
}

bool chargeDia::isVisitor(QString carid)
{
    QSqlDatabase dbM = QSqlDatabase::database("MEMORY");
    QSqlQuery queryM(dbM);
    QString sel=QString("select * from reserveCar where car_id='%1';").arg(carid);
    queryM.exec(sel);
    if(!queryM.next()){
         return false;
    }
    else{
         return true;
    }
}

void chargeDia::charge(QString carid){
    int fee;
    if(!isVisitor(carid)){
         fee=0;
    }
    QString feeAsString = QString::number(fee)+"元";
    ui->label_21->setText(feeAsString);
}




void chargeDia::on_pushButton_5_clicked()
{
 // 创建一个 QMessageBox 对话框
    QMessageBox messageBox(this);

    // 设置对话框的标题和文本
    messageBox.setWindowTitle("提示");
    messageBox.setText("收费金额");

    // 添加按钮
    QPushButton *button1 = messageBox.addButton("微信", QMessageBox::AcceptRole);
    QPushButton *button2 = messageBox.addButton("支付宝", QMessageBox::RejectRole);
    QPushButton *button3 = messageBox.addButton("现金", QMessageBox::DestructiveRole);

    // 显示对话框，并等待用户响应
    QString vehicle_id=ui->label_14->text();
    QString inh=ui->label_15->text();   //入校时间
    QString outh=ui->label_16->text();  //出校时间
    QString inp=ui->label_19->text();   //入校门
    QString outp=ui->label_20->text();  //出校门
    int entryDoorId=selectdoorID(inp);
    int exitDoorId=selectdoorID(outp);
    QString f=ui->label_21->text();
    QString f1=f.left(f.length()-1);
    int parkf=f1.toInt();   //收费金额
    QString payw;

    //读取车辆类别
    QString typeV=ui->comboBox->currentText();
    QString typeData;
    if (typeV == "内部车辆") {
         typeData="Internal";
    } else if (typeV == "登记收费车") {
         typeData="Registed";
    } else if (typeV == "来访车") {
         typeData="Visitor";
    } else {
        qDebug()<<"车辆类别，数据库里没有这个选择";
    }

    messageBox.exec();
    QSqlDatabase db= QSqlDatabase::database("DISK");
    QSqlQuery query(db);
    QSqlDatabase dbM= QSqlDatabase::database("MEMORY");
    QSqlQuery queryM(dbM);
    // 根据用户的响应进行处理
    if (messageBox.clickedButton() == button1) {
        payw="wechat";
    } else if (messageBox.clickedButton() == button2) {
         payw="alipay";
    } else if (messageBox.clickedButton() == button3) {
         payw="cash";
    }



    // 开始事务并锁定表格
    QSqlQuery lockQuery(db);
    QSqlQuery lockQueryM(dbM);


    //写内存数据库
    // 开始事务
    if (dbM.transaction()) {
         QString inM=QString("INSERT INTO CurrentAccess (VehicleID, EntryDoorID, ExitDoorID, EntryTime, ExitTime) VALUES ('%1','%2','%3','%4','%5');").arg(vehicle_id).arg(entryDoorId).arg(exitDoorId).arg(inh).arg(outh);

         // 执行写入表的操作
         queryM.exec(inM);
         if (queryM.lastError().isValid()) {
            qDebug() << "写入表出错:" << queryM.lastError().text();
            dbM.rollback(); // 回滚事务
         } else {
            dbM.commit(); // 提交事务
            qDebug() << "写入表成功";
         }
    } else {
         qDebug() << "无法开始事务:" << dbM.lastError().text();
    }
    //写磁盘数据库
    lockQuery.exec("START TRANSACTION;");
    lockQuery.exec("LOCK TABLES AccessHistory WRITE;");
    QString in=QString("INSERT INTO AccessHistory (VehicleID, EntryDoorID, ExitDoorID, EntryTime, ExitTime) VALUES ('%1','%2','%3','%4','%5');").arg(vehicle_id).arg(entryDoorId).arg(exitDoorId).arg(inh).arg(outh);
    if(query.exec(in)){
         qDebug() << "出入校门数据插入成功";
    }
    else{
         qDebug() << "出入校门数据插入失败:" << query.lastError().text();
    }

    lockQuery.exec("LOCK TABLES ParkingFee WRITE;");
    QString inFee=QString("INSERT INTO ParkingFee (VehicleID, EntryTime, ExitTime, FeeAmount, PayWay,VehicleType) VALUES ('%1','%2','%3','%4','%5','%6');").arg(vehicle_id).arg(inh).arg(outh).arg(parkf).arg(payw).arg(typeData);
    if(query.exec(inFee)){
          qDebug() << "收费数据插入成功";
    }
    else{
          qDebug() << "收费数据插入失败:" << query.lastError().text();
    }

    // 提交事务以释放锁定
    lockQuery.exec("UNLOCK TABLES;");
    lockQuery.exec("COMMIT;");
//    query.exec("select * from comeCar;");
//    while(queryM.next()){
//         qDebug()<<queryM.value(0).toString()<<queryM.value(1).toString()<<queryM.value(2).toString()<<queryM.value(3).toString()<<queryM.value(4).toString()<<queryM.value(5).toString()<<queryM.value(6).toString()<<queryM.value(7).toString();
//    }
    messageBox.close();
}

int chargeDia::selectdoorID(QString doorName){
    QSqlDatabase db= QSqlDatabase::database("DISK");
    QSqlQuery query(db);
    query.prepare("SELECT DoorID FROM Doors WHERE DoorName = ?");
    // 绑定占位符的值为 doorName 变量
    query.bindValue(0, doorName);

    // 执行查询
    if (query.exec()) {
         while (query.next()) {
            int doorID = query.value(0).toInt();
            return doorID;
            // 在这里使用 doorID
         }
    } else {
         qDebug() << "查询失败: " << query.lastError().text();
         }
    return 0;
}

