#include "login.h"
#include "manage1.h"
#include "connection.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    //界面
    ui->user->setPlaceholderText("管理员账号");
    ui->password->setPlaceholderText("管理员密码");
    //设置密文登录
    ui->password->setEchoMode(QLineEdit::Password);

    QAction *action = new QAction(this);
    action->setIcon(QIcon(":/new/prefix1/UIImages/account.png"));
    ui->user->addAction(action,QLineEdit::LeadingPosition);

    QAction *action2 = new QAction(this);
    action2->setIcon(QIcon(":/new/prefix1/UIImages/password.png"));
    ui->password->addAction(action2,QLineEdit::LeadingPosition);

    if(!isDatabaseConnected("DISK")){
        createConnection();
    }
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
    QString InUser=ui->user->text();
    QString InPass=ui->password->text();
    QSqlDatabase db = QSqlDatabase::database("DISK");
    QSqlQuery query(db);     //此时在构建QSqlQuery对象时传入自定义的db，否则QSqlQuery无法使用
    QString selM=QString("select password from ManageMember where username='%1';").arg(InUser);
    query.exec(selM);
    if(!query.next()||query.value(0).toString()!=InPass){
        QMessageBox::warning(this,tr("登录失败"),tr("请输入正确的校内人员信息"),QMessageBox::Ok);
        ui->user->clear();
        ui->password->clear();
        ui->user->setFocus();
    }
    else{
        QString selR=QString("select role from ManageMember where username='%1';").arg(InUser);
        query.exec(selR);
        query.next();
        QString role=query.value(0).toString();
        this->close();
        Manage1 *m=new Manage1;
        m->receiveRole(role);
        m->show();
    }
}

