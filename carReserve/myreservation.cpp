#include "myreservation.h"
#include "ui_myreservation.h"

myreservation::myreservation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myreservation)
{
    ui->setupUi(this);

    //预约信息表i
    ui->reserveTable->setRowCount(2);   //2行
    ui->reserveTable->setColumnCount(4);   //2列
    ui->reserveTable->setFrameShape(QFrame::NoFrame); //设置边框
    ui->reserveTable->setFixedSize(641,101);   //固定大小
    ui->reserveTable->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->reserveTable->horizontalHeader()->setVisible(false);   //设置水平头不可见
    //ui->reserveTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->reserveTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条
    ui->reserveTable->setFont(QFont("Helvetica"));

    ui->reserveTable->setColumnWidth(0,60);
    ui->reserveTable->setColumnWidth(1,261);
    ui->reserveTable->setColumnWidth(2,160);
    ui->reserveTable->setColumnWidth(3,160);
    ui->reserveTable->verticalHeader()->setDefaultSectionSize(15);
    ui->reserveTable->setRowHeight(0,25);
    ui->reserveTable->setAlternatingRowColors(true);
    ui->reserveTable->setFrameShape(QFrame::NoFrame); //设置边框
    ui->reserveTable->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    QPalette palette;    //调色板
    palette.setColor(QPalette::Base, QColor(255,255,255));   //基底
    palette.setColor(QPalette::AlternateBase, QColor(233,245,252));  //交替基底
    ui->reserveTable->setPalette(palette);

    //表头列文本设置
    ui->reserveTable->setItem(0, 0, new QTableWidgetItem("序号"));
    ui->reserveTable->setItem(0, 1, new QTableWidgetItem("来访人姓名"));
    ui->reserveTable->setItem(0, 2, new QTableWidgetItem("车牌号码"));
    ui->reserveTable->setItem(0, 3, new QTableWidgetItem("预约时间"));

    ui->reserveTable->item(0,0)->setForeground(Qt::white);
    ui->reserveTable->item(0,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->reserveTable->item(0,0)->setBackground(QColor(0, 114, 169));
    ui->reserveTable->item(0,0)->setFont(QFont("Helvetica",10));

    ui->reserveTable->item(0,1)->setForeground(Qt::white);
    ui->reserveTable->item(0,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->reserveTable->item(0,1)->setBackground(QColor(0, 114, 169));
    ui->reserveTable->item(0,1)->setFont(QFont("Helvetica",10));

    ui->reserveTable->item(0,2)->setForeground(Qt::white);
    ui->reserveTable->item(0,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->reserveTable->item(0,2)->setBackground(QColor(0, 114, 169));
    ui->reserveTable->item(0,2)->setFont(QFont("Helvetica",10));

    ui->reserveTable->item(0,3)->setForeground(Qt::white);
    ui->reserveTable->item(0,3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->reserveTable->item(0,3)->setBackground(QColor(0, 114, 169));
    ui->reserveTable->item(0,3)->setFont(QFont("Helvetica",10));

    ui->reserveTable->item(0,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->reserveTable->item(0,0)->setFlags(ui->reserveTable->item(0,0)->flags()&~Qt::ItemIsSelectable);
    ui->reserveTable->item(0,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->reserveTable->item(0,1)->setFlags(ui->reserveTable->item(0,0)->flags()&~Qt::ItemIsSelectable);
    ui->reserveTable->item(0,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->reserveTable->item(0,2)->setFlags(ui->reserveTable->item(0,0)->flags()&~Qt::ItemIsSelectable);
    ui->reserveTable->item(0,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->reserveTable->item(0,3)->setFlags(ui->reserveTable->item(0,0)->flags()&~Qt::ItemIsSelectable);
}

myreservation::~myreservation()
{
    delete ui;
}

void myreservation::on_pushButton_clicked()
{
    this->close();
    MainWindow *mw=new MainWindow();
    mw->show();
}

