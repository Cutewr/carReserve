#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<chargedia.h>
#include<countdia.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    chargeDia* mycharge;
    countdia* mycount;

public:
    QMap<QString, QString> countFee(QString type,QString payw);
};
#endif // MAINWINDOW_H
