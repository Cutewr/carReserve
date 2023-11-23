#ifndef MANAGE1_H
#define MANAGE1_H
#include "login.h"

#include <QWidget>


namespace Ui {
class Manage1;
}

class Manage1 : public QWidget
{
    Q_OBJECT

public:
    explicit Manage1(QWidget *parent = nullptr);
    ~Manage1();

private:
    Ui::Manage1 *ui;


signals:
    void writeData(const char* buf, qint64 len);
    void stopWork();

public:
    void table();
    void receiveRole(QString role);
private slots:
    void on_pushButton_clicked();
};

#endif // MANAGE1_H
