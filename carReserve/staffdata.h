#ifndef STAFFDATA_H
#define STAFFDATA_H

#include <QWidget>

namespace Ui {
class StaffData;
}

class StaffData : public QWidget
{
    Q_OBJECT

public:
    explicit StaffData(QWidget *parent = nullptr);
    ~StaffData();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::StaffData *ui;
};

#endif // STAFFDATA_H
