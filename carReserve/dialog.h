#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h" //必须引入

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QWidget *m_widget;
};

#endif // DIALOG_H
