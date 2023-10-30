#include "success.h"
#include "ui_success.h"

success::success(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::success)
{
    ui->setupUi(this);
}

success::~success()
{
    delete ui;
}
