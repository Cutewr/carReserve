#include "charge.h"
#include "ui_charge.h"

charge::charge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::charge)
{
    ui->setupUi(this);

    mycharge =new chargeDia(this);
    connect(ui->pushButton,&QPushButton::clicked,mycharge,&chargeDia::open);
}

charge::~charge()
{
    delete ui;
}

void charge::on_pushButton_clicked()
{

}

