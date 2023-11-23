#include "manage1.h"
#include "ui_manage1.h"

Manage1::Manage1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manage1)
{
    ui->setupUi(this);

    ui->label->installEventFilter(this);    // 安装事件过滤器
    ui->scrollArea->setGeometry(0, 0, 671, 578);//主界面参数
    ui->scrollArea->setWidgetResizable(false);//可以拖动滚动条
    //竖滚动条和横滚动条都可以一直显示
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置主界面的实际界面
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setGeometry(0, 0, 671, 1021);//实际界面参数

    table();
}

Manage1::~Manage1()
{
    delete ui;
}

void Manage1::receiveRole(QString role){
    if(role=="admin"){
        qDebug()<<"超级管理员";
    }
    else if(role=="auditor"){
        qDebug()<<"审核员";
    }
}

void Manage1::table()
{
    ui->table->setRowCount(2);   //2行
    ui->table->setColumnCount(3);   //2列
    ui->table->setFrameShape(QFrame::NoFrame); //设置边框
    ui->table->setFixedSize(550,101);   //固定大小
    ui->table->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->table->horizontalHeader()->setVisible(false);   //设置水平头不可见
    ui->table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条
    ui->table->setFont(QFont("Helvetica"));

    ui->table->setColumnWidth(0,140);
    ui->table->setColumnWidth(1,200);

    ui->table->verticalHeader()->setDefaultSectionSize(15);
    ui->table->setRowHeight(0,25);
    ui->table->setAlternatingRowColors(true);
    ui->table->setFrameShape(QFrame::NoFrame); //设置边框
    ui->table->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    QPalette palette;    //调色板
    palette.setColor(QPalette::Base, QColor(255,255,255));   //基底
    palette.setColor(QPalette::AlternateBase, QColor(233,245,252));  //交替基底
    ui->table->setPalette(palette);

    //表头列文本设置
    ui->table->setItem(0, 0, new QTableWidgetItem("姓名"));
    ui->table->setItem(0, 1, new QTableWidgetItem("身份证号"));

    ui->table->item(0,0)->setForeground(Qt::white);
    ui->table->item(0,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->table->item(0,0)->setBackground(QColor(0, 114, 169));
    ui->table->item(0,0)->setFont(QFont("Helvetica",10));

    ui->table->item(0,1)->setForeground(Qt::white);
    ui->table->item(0,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->table->item(0,1)->setBackground(QColor(0, 114, 169));
    ui->table->item(0,1)->setFont(QFont("Helvetica",10));

    ui->table->item(0,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->table->item(0,0)->setFlags(ui->table->item(0,0)->flags()&~Qt::ItemIsSelectable);
    ui->table->item(0,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->table->item(0,1)->setFlags(ui->table->item(0,0)->flags()&~Qt::ItemIsSelectable);
}

void Manage1::on_pushButton_clicked()
{
    this->close();
    login *l=new login();
    l->show();
}

