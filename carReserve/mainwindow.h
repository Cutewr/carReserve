#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>//必须引入
#include "dialog.h" //必须引入
#include <QMouseEvent>
#include<QTableWidget>
#include <QLineEdit>
#include"qhmaskwidget.h"
#include "myreservation.h"
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWIndow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_AddButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_lineEdit_3_editingFinished();

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void receiveMessage();
    void on_pushButton_2_clicked();

private:
    Ui::MainWIndow *ui;
    QDialog *dialog;//定义一个弹窗的指针
    QHMaskWidget *m_mask;
    QTcpSocket *socket;
    bool validateID(QString id);
    void msgBox(QString banner);

public:
    void DealOut();//定义一个函数来弹出协议窗口
    void table();


public:
    bool eventFilter(QObject *obj, QEvent *event);	// 添加时间过滤器声明
};
#endif // MAINWINDOW_H
