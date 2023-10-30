#include "staffdata.h"
#include "ui_staffdata.h"

StaffData::StaffData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaffData)
{
    ui->setupUi(this);
}

StaffData::~StaffData()
{
    delete ui;
}

void StaffData::on_pushButton_2_clicked()
{

}

