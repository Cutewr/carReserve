#ifndef COUNTDIA_H
#define COUNTDIA_H

#include <QDialog>
#include "QTimeEdit"
#include "QInputDialog"
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <vector>

namespace Ui {
class countdia;
}

class countdia : public QDialog
{
    Q_OBJECT

public:
    explicit countdia(QWidget *parent = nullptr);
    ~countdia();


private:
    Ui::countdia *ui;



public:
    void table();
    void processData(const std::vector<QMap<QString, QString>>& vectorOfMaps);


private slots:
    void on_pushButton_5_clicked();
    void showCustomDateTimeDialog();

};

#endif // COUNTDIA_H
