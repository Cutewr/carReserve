#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //connect(QpushButton, SIGNAL(clicked()), this, SLOT(OkButtonPressSlot()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    close();
    m_widget = new QWidget(this);
    m_widget->close();
}

