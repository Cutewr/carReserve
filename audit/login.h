#ifndef LOGIN_H
#define LOGIN_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "manage1.h"


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
    bool isDatabaseConnected(const QString &connectionName){
        if (QSqlDatabase::contains(connectionName)){
            QSqlDatabase db=QSqlDatabase::database(connectionName);
            if(db.isOpen()){
                return true;
            }
            else{
                return false;
            }
        }
    }
};
#endif // LOGIN_H
