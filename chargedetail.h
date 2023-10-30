#ifndef CHARGEDETAIL_H
#define CHARGEDETAIL_H

#include <QDialog>

namespace Ui {
class chargeDetail;
}

class chargeDetail : public QDialog
{
    Q_OBJECT

public:
    explicit chargeDetail(QWidget *parent = nullptr);
    ~chargeDetail();
    void sendData(QString data,QString fee); //在子窗口创建public函数用来获取传递的数据
    void isStaff();


private slots:
    void on_pushButton_clicked();

private:
    Ui::chargeDetail *ui;
};

#endif // CHARGEDETAIL_H
