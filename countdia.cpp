#include "countdia.h"
#include "ui_countdia.h"
#include "connectionData.h"
#include "QDateTime"
#include <QDateTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include<QSqlError>
#include "datetimedialog.h" // 包含DateTimeDialog头文件


countdia::countdia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::countdia)
{
    ui->setupUi(this);
    table();

    ui->label_16->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    // 连接按钮点击信号到槽函数
    connect(ui->pushButton, &QPushButton::clicked, this, &countdia::showCustomDateTimeDialog);
}

countdia::~countdia()
{
    delete ui;
}

void countdia::on_pushButton_5_clicked()
{   
    QSqlDatabase dbM = QSqlDatabase::database("MEMORY");
    QSqlQuery queryM(dbM);

    QString sel=QString("select count(*) from CurrentAccess");
    queryM.exec(sel);
    queryM.next();
    //预约的车数量
    int count=queryM.value(0).toInt();
    qDebug()<<count;    //今天来访的车数量
    this->close();
}

void countdia::showCustomDateTimeDialog()
{
    DateTimeDialog dialog(nullptr);
    if (dialog.exec() == QDialog::Accepted) {
        QDateTime selectedDateTime = dialog.getSelectedDateTime();
        QString selectedDateTimeString = selectedDateTime.toString("yyyy-MM-dd hh:mm:ss");
        // 在这里使用 selectedDateTimeString 或执行其他操作
        ui->label->setText(selectedDateTimeString);
    }
}

void countdia::table()
{
    ui->counttable->setRowCount(4);   //2行
    ui->counttable->setColumnCount(4);   //2列
    ui->counttable->setFrameShape(QFrame::NoFrame); //设置边框
    ui->counttable->setFixedSize(590,102);   //固定大小
    ui->counttable->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->counttable->horizontalHeader()->setVisible(false);   //设置水平头不可见
    //ui->counttable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->counttable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条
    ui->counttable->setFont(QFont("Helvetica"));

    ui->counttable->setColumnWidth(0,110);
    ui->counttable->setColumnWidth(1,160);
    ui->counttable->setColumnWidth(2,160);
    ui->counttable->setColumnWidth(3,160);

    ui->counttable->verticalHeader()->setDefaultSectionSize(25);
    ui->counttable->setAlternatingRowColors(true);
    ui->counttable->setFrameShape(QFrame::NoFrame); //设置边框
    ui->counttable->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    QPalette palette;    //调色板
    palette.setColor(QPalette::Base, QColor(233,245,252));   //基底
    palette.setColor(QPalette::AlternateBase, QColor(233,245,252));  //交替基底
    ui->counttable->setPalette(palette);

    //统计车的数量和费用
    QTableWidgetItem *defaultItem = new QTableWidgetItem("0.0元 | 0辆");

    // 设置表格的默认单元格值
    for (int row = 1; row < ui->counttable->rowCount(); ++row) {
        for (int col = 1; col < ui->counttable->columnCount(); ++col) {
            QTableWidgetItem *item = defaultItem->clone(); // 克隆默认单元格
            item->setTextAlignment(Qt::AlignCenter); // 设置文本居中对齐
            ui->counttable->setItem(row, col, item);
        }
    }

    //表头列文本设置
    ui->counttable->setItem(0, 0, new QTableWidgetItem("车辆类别"));
    ui->counttable->setItem(0, 1, new QTableWidgetItem("微信(金额|车辆数)"));

    ui->counttable->setItem(3, 0, new QTableWidgetItem("登记车辆"));
    ui->counttable->setItem(2, 0, new QTableWidgetItem("来访车"));
    ui->counttable->setItem(1, 0, new QTableWidgetItem("内部车"));

    ui->counttable->setItem(0, 2, new QTableWidgetItem("支付宝(金额|车辆数)"));
    ui->counttable->setItem(0, 3, new QTableWidgetItem("现金(金额|车辆数)"));

    ui->counttable->item(0,0)->setForeground(Qt::white);
    ui->counttable->item(0,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->counttable->item(0,0)->setBackground(QColor(0, 114, 169));
    ui->counttable->item(0,0)->setFont(QFont("Helvetica",10));

    ui->counttable->item(0,1)->setForeground(Qt::white);
    ui->counttable->item(0,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->counttable->item(0,1)->setBackground(QColor(0, 114, 169));
    ui->counttable->item(0,1)->setFont(QFont("Helvetica",10));

    ui->counttable->item(0,2)->setForeground(Qt::white);
    ui->counttable->item(0,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->counttable->item(0,2)->setBackground(QColor(0, 114, 169));
    ui->counttable->item(0,2)->setFont(QFont("Helvetica",10));

    ui->counttable->item(0,3)->setForeground(Qt::white);
    ui->counttable->item(0,3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->counttable->item(0,3)->setBackground(QColor(0, 114, 169));
    ui->counttable->item(0,3)->setFont(QFont("Helvetica",10));

    ui->counttable->item(1,0)->setForeground(Qt::white);
    ui->counttable->item(1,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->counttable->item(1,0)->setBackground(QColor(0, 114, 169));
    ui->counttable->item(1,0)->setFont(QFont("Helvetica",10));

    ui->counttable->item(2,0)->setForeground(Qt::white);
    ui->counttable->item(2,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->counttable->item(2,0)->setBackground(QColor(0, 114, 169));
    ui->counttable->item(2,0)->setFont(QFont("Helvetica",10));

    ui->counttable->item(3,0)->setForeground(Qt::white);
    ui->counttable->item(3,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->counttable->item(3,0)->setBackground(QColor(0, 114, 169));
    ui->counttable->item(3,0)->setFont(QFont("Helvetica",10));

    ui->counttable->item(0,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);    //不可选中
    ui->counttable->item(0,0)->setFlags(ui->counttable->item(0,0)->flags()&~Qt::ItemIsSelectable);  //不可编辑
    ui->counttable->item(0,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->counttable->item(0,1)->setFlags(ui->counttable->item(0,1)->flags()&~Qt::ItemIsSelectable);
    ui->counttable->item(0,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->counttable->item(0,2)->setFlags(ui->counttable->item(0,2)->flags()&~Qt::ItemIsSelectable);
    ui->counttable->item(0,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->counttable->item(0,3)->setFlags(ui->counttable->item(0,3)->flags()&~Qt::ItemIsSelectable);
    ui->counttable->item(1,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->counttable->item(1,0)->setFlags(ui->counttable->item(1,0)->flags()&~Qt::ItemIsSelectable);
    ui->counttable->item(2,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->counttable->item(2,0)->setFlags(ui->counttable->item(2,0)->flags()&~Qt::ItemIsSelectable);
    ui->counttable->item(3,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->counttable->item(3,0)->setFlags(ui->counttable->item(3,0)->flags()&~Qt::ItemIsSelectable);
}

void countdia::processData(const std::vector<QMap<QString, QString>>& data){
    //统计车的数量和费用
    QStringList myList;
    for (const QMap<QString, QString>& map : data) {
        // 使用 map 中的键值对
        QMap<QString, QString>::const_iterator it;
        for (it = map.constBegin(); it != map.constEnd(); ++it) {
            QString key = it.key();
            QString value = it.value();
            QString countTemp=value+".0元 | "+key+"辆";
            myList.append(countTemp);
        }
    }
    int k=0;
    for (int row = 1; row < 3; row++) {
        for (int col = 1; col < ui->counttable->columnCount(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(myList.at(k));
            item->setTextAlignment(Qt::AlignCenter); // 设置文本居中对齐
            ui->counttable->setItem(row, col, item);
            k++;
        }
    }
}

