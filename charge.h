#ifndef CHARGE_H
#define CHARGE_H

#include <QWidget>
#include<chargedia.h>

namespace Ui {
class charge;
}

class charge : public QWidget
{
    Q_OBJECT

public:
    explicit charge(QWidget *parent = nullptr);
    ~charge();

private slots:
    void on_pushButton_clicked();

private:
    Ui::charge *ui;
    chargeDia* mycharge;
};

#endif // CHARGE_H
