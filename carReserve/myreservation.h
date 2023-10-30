#ifndef MYRESERVATION_H
#define MYRESERVATION_H
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class myreservation;
}

class myreservation : public QWidget
{
    Q_OBJECT

public:
    explicit myreservation(QWidget *parent = nullptr);
    ~myreservation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::myreservation *ui;
};

#endif // MYRESERVATION_H
