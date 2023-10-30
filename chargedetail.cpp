#include "chargedetail.h"
#include "ui_chargedetail.h"

chargeDetail::chargeDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chargeDetail)
{
    ui->setupUi(this);

}

chargeDetail::~chargeDetail()
{
    delete ui;
}

void chargeDetail::on_pushButton_clicked()
{
    this->close();
}

void chargeDetail::sendData(QString data,QString fee)
{
    ui->label->setText(data);
  //  ui->label_2->setText(fee);
    ui->label_4->setText(fee);
}

void chargeDetail::isStaff(){
    ui->label_3->setText("校内车");
    ui->label_4->setText("0元");
}

