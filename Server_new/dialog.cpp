#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QThread>

#include "server.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "dataConnect.h"
#include<QSqlError>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_server(new Server(this)),
    m_count(0)
{
    ui->setupUi(this);
    createConnection();
    setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);

    ui->labelNum->setText(QString("%1").arg(m_count));

    m_server = new Server(this);
    m_server->listen(QHostAddress::Any, 8712);

    connect(ui->btnSend,        SIGNAL(clicked()),      this, SLOT(sendDataSlot()));
    connect(ui->btnClear,       SIGNAL(clicked()),      this, SLOT(clearData()));

    timer=new QTimer(this);
    timer->setInterval(1000*60);
    connect(timer,SIGNAL(timeout()),this,SLOT(insert()));
    timer->start();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showConnection(int sockDesc)
{
    m_count++;
    ui->comboBoxObj->addItem(QString("%1").arg(sockDesc), sockDesc);
    ui->labelNum->setText(QString("%1").arg(m_count));
}

void Dialog::insertQString(const QString &text)
{
    // 确保线程安全，可以使用QMutexLocker
    QMutexLocker locker(&mutex);
    insertList.append(text);
    insertListBuffer.append(text);
}

void Dialog::insert()
{
    QSqlDatabase db = QSqlDatabase::database("DISK");
    QSqlQuery query(db);
    QStringList::ConstIterator it;
    for(it=insertListBuffer.constBegin();it!=insertListBuffer.constEnd();it++){
        QString item=*it;
        qDebug()<<item;
        if(!query.exec(item)){
            qDebug()<<query.lastError().text();
            return;
        }
    }
    insertListBuffer.clear();
}

void Dialog::showDisconnection(int sockDesc)
{
    m_count--;
    ui->comboBoxObj->clear();

    int index = ui->comboBoxObj->findData(sockDesc);
    ui->comboBoxObj->removeItem(index);

    ui->labelNum->setText(QString("%1").arg(m_count));
}


void Dialog::sendDataSlot(void)
{
    if (ui->lineEditMsg->text().isEmpty()) {
        QMessageBox::information(Q_NULLPTR, QString("注意"), QString("发送内容不能为空！"), QMessageBox::Yes);
        return ;
    }
    ui->lineEditMsg->setText("");
}

void Dialog::recvData(const QString &ip, const QByteArray &data)
{
    QString msg;

    if (!ui->checkBoxHideIP->isChecked()) {
        msg += ip + QString(": ");
    }
    msg += QString::fromLocal8Bit(data) + "\n";
    ui->textBrowser->append(msg);
}

void Dialog::clearData(void)
{
    ui->textBrowser->clear();
}

