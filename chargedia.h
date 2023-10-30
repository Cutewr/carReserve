#ifndef CHARGEDIA_H
#define CHARGEDIA_H

#include <QDialog>
#include "chargedetail.h"
#include"qhmaskwidget.h"


namespace Ui {
class chargeDia;
}

class chargeDia : public QDialog
{
    Q_OBJECT


public:
    explicit chargeDia(QWidget *parent = nullptr);
    ~chargeDia();



private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    bool isVisitor(QString carid);

    void charge(QString carid);

    void on_pushButton_5_clicked();

private:
    Ui::chargeDia *ui;
    QHMaskWidget *m_mask;
    chargeDetail* detail1;
    int selectdoorID(QString doorName);
};

#endif // CHARGEDIA_H
