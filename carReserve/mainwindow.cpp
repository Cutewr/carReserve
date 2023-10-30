#include "mainwindow.h"
#include "connection.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include "QFileDialog"
#include <QRegularExpression>
#include <QTableWidget>
#include <QHBoxLayout>
#include<QStringList>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QCheckBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWIndow)
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);
    //客户端连接服务器
    socket->connectToHost("211.69.197.182",8712);
    if(socket->waitForConnected(10000)){
        msgBox("连接服务器成功");
    }
    else{
        msgBox("连接失败，请检查IP地址和端口");
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));

    QFile qss("qrc:/style.qss"); //.qss文件路径

    ui->scrollArea->setGeometry(0, 0, 671, 578);//主界面参数
    ui->scrollArea->setWidgetResizable(false);//可以拖动滚动条
    //竖滚动条和横滚动条都可以一直显示
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置主界面的实际界面
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setGeometry(0, 0, 671, 1021);//实际界面参数

    //访问事由 复选框
    QStringList strList;
    strList<<"因公往来"<<"私事来访";
    ui->comboBox->addItems(strList);

    table();

    //阅读所有协议
    QString strText = QString("<font color=black>%1</font>").arg("我已认真阅读并同意") + QString("<font color=\"#6495ED\">%1</font>").arg("全部协议");
    ui->label->setText(strText);

    //预约时间设置
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(3));
    ui->dateEdit->setDisplayFormat("yyyy.MM.dd");

    ui->label->installEventFilter(this);    // 安装事件过滤器
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QFileDialog ask_for_dir(this);
    if(ask_for_dir.exec()==0)   return;
}

//点击出现阅读协议
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label)//指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

            if(mouseEvent->button() == Qt::LeftButton)
            {
                dialog = new Dialog(this);
                dialog->setModal(false);
                //dialog->show();
                // 遮罩窗口.
                m_mask=new QHMaskWidget(this);
                // 嵌入窗口.
                m_mask->addEmbeddedWindow(dialog);
                m_mask->show();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        // pass the event on to the parent class
        return QWidget::eventFilter(obj, event);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString campus;
    if(ui->checkBox->isChecked()==true)
    {
        campus=QString("main");
    }else if (ui->checkBox_2->isChecked()==true) {
        campus=QString("tongji");
    }
    QString staff_name=ui->lineEdit_2->text();
    QString staff_no=ui->lineEdit->text();
    QVariant recause=ui->comboBox->currentText();
    QString cause=recause.toString();
    if(cause=="因公往来"){
        cause="official";
    }
    else{
        cause="personal";
    }
    QDate reserve_date = ui->dateEdit->date();  // 日期
    QString redate=reserve_date.toString("yyyy-MM-dd");

    if(ui->checkBox_2->isChecked()==false && ui->checkBox->isChecked()==false){
        msgBox("请选择所属校区");
        return;
    }

    if(ui->checkBox_3->isChecked()==false && ui->checkBox_5->isChecked()==false){
        msgBox("请选择入校方式");
        return;
    }
    QString way;
    if(ui->checkBox_3->isChecked()==true)
    {
        way=QString("walk");
    }else if (ui->checkBox_5->isChecked()==true) {
        way=QString("drive");
        if(ui->lineEdit_3->text().isEmpty()){
            msgBox("请输入车牌号码");
            return;
        }
    }
    QString vehicle_id=ui->lineEdit_3->text();

    //来访人员信息是否填写
    if(ui->table->item(1,0)==NULL || ui->table->item(1,1)==NULL){
        msgBox("请填写来访人员信息");
        return;
    }
    else if(ui->table->item(1,0)->text().isEmpty() || ui->table->item(1,1)->text().isEmpty()){
        msgBox("请填写来访人员信息");
        return;
    }
    QString id1=ui->table->item(1,1)->text();
    int i;
    int nRow=ui->table->rowCount();
    //判断输入身份证号是否正确
    for(i=1;i<nRow;i++){
        if(!validateID(ui->table->item(i,1)->text())){
            msgBox("请输入正确的来访人员身份证号");
            return;
        }
    }

    if(ui->radioButton->isChecked()==false){
       msgBox("请先阅读并同意上述协议");
       return;
    }

    //创建json数组获取游客信息
    QJsonArray jsonArray;
    for(i=1;i<nRow;i++){
       QJsonObject visitor;
        QString name=ui->table->item(i,0)->text();
        QString id=ui->table->item(i,1)->text();
        visitor["name"]=name;
        visitor["id"]=id;
        jsonArray.append(visitor);
    }

    // 创建一个JSON对象并填充数据
    QJsonObject jsonObject;
    jsonObject["name"] = staff_name;
    jsonObject["no"] = staff_no;
    jsonObject["redate"] = redate;
    jsonObject["way"] = way;
    jsonObject["cause"] = cause;
    jsonObject["vehicle_id"] = vehicle_id;
    jsonObject["visitor_id"] = id1;

    QJsonObject jsonData;
    jsonData["data"]=jsonObject;
    jsonData["dataArray"]=jsonArray;
    // 将JSON对象转换为JSON文档
    QJsonDocument jsonDocument(jsonData);
    // 将JSON文档转换为字节数组
    QByteArray jsonDataToSend = jsonDocument.toJson();

    // 发送JSON数据到服务器
    socket->write(jsonDataToSend);
    socket->waitForBytesWritten();
}

void MainWindow::on_AddButton_clicked()
{
    // 在tableWidget里插入项
    int nRow = ui->table->rowCount();
    if(nRow>=5){
        msgBox("最多添加4人");
        return;
    }
    ui->table->setRowCount(nRow+1);

    //ui->table->setCellWidget(nRow+1, 1, Widget_input2);
    //    // 删除按钮
    //    QPushButton* pBtnDelete = new QPushButton(QStringLiteral("删除"));
    //pBtnDelete->setProperty("item", QVariant::fromValue(pItem1));
    //connect(pBtnDelete, &QPushButton::clicked, this, &QtableWidgetNB::sltBtnDeleteClicked);
}



void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    myreservation *myre=new myreservation();
    myre->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    this->close();
}

void MainWindow::table()
{
    ui->table->setRowCount(2);   //2行
    ui->table->setColumnCount(2);   //2列
    ui->table->setFrameShape(QFrame::NoFrame); //设置边框
    ui->table->setFixedSize(550,101);   //固定大小
    ui->table->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->table->horizontalHeader()->setVisible(false);   //设置水平头不可见
    ui->table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条
    ui->table->setFont(QFont("Helvetica"));

    ui->table->setColumnWidth(0,140);
    ui->table->setColumnWidth(1,200);

    ui->table->verticalHeader()->setDefaultSectionSize(15);
    ui->table->setRowHeight(0,25);
    ui->table->setAlternatingRowColors(true);
    ui->table->setFrameShape(QFrame::NoFrame); //设置边框
    ui->table->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    QPalette palette;    //调色板
    palette.setColor(QPalette::Base, QColor(255,255,255));   //基底
    palette.setColor(QPalette::AlternateBase, QColor(233,245,252));  //交替基底
    ui->table->setPalette(palette);

    //表头列文本设置
    ui->table->setItem(0, 0, new QTableWidgetItem("姓名"));
    ui->table->setItem(0, 1, new QTableWidgetItem("身份证号"));

    ui->table->item(0,0)->setForeground(Qt::white);
    ui->table->item(0,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->table->item(0,0)->setBackground(QColor(0, 114, 169));
    ui->table->item(0,0)->setFont(QFont("Helvetica",10));

    ui->table->item(0,1)->setForeground(Qt::white);
    ui->table->item(0,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->table->item(0,1)->setBackground(QColor(0, 114, 169));
    ui->table->item(0,1)->setFont(QFont("Helvetica",10));

    ui->table->item(0,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->table->item(0,0)->setFlags(ui->table->item(0,0)->flags()&~Qt::ItemIsSelectable);
    ui->table->item(0,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    ui->table->item(0,1)->setFlags(ui->table->item(0,0)->flags()&~Qt::ItemIsSelectable);
}

bool MainWindow::validateID(QString id) {
    // 定义身份证号码的正则表达式
    QRegularExpression regex("^[1-9]\\d{5}(18|19|20)\\d{2}(0\\d|10|11|12)([0-2]\\d|30|31)\\d{3}[0-9Xx]$");
    // 使用正则表达式验证身份证号码
    QRegularExpressionMatch match = regex.match(id);
    if (match.hasMatch()) {
        return true; // 身份证格式正确
    } else {
        return false; // 身份证格式不正确
    }
}

void MainWindow::msgBox(QString banner){
    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{"
                         "min-width:150px;"
                         "min-height:40px; "
                         "font-size:16px;}");
    msgBox.setText(banner);
    msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
}

void MainWindow::on_lineEdit_3_editingFinished()
{
    QString licensePlate=ui->lineEdit_3->text().toUpper();// 转换为大写以匹配正则表达式
    QRegularExpression licensePlateRegex;
    licensePlateRegex.setPattern("^[京津冀晋蒙辽吉黑沪苏浙皖闽赣鲁豫鄂湘粤桂琼渝川贵云藏陕甘青宁新]{1}[A-Z0-9]{5,7}$");
    QRegularExpressionMatch match = licensePlateRegex.match(licensePlate);
    if (match.hasMatch()) {
        return;
    } else{
        msgBox("错误的车牌号格式");
    }
}


void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(ui->checkBox_3->isChecked()){
        ui->checkBox_5->setChecked(false);
    }
}


void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(ui->checkBox_5->isChecked()){
        ui->checkBox_3->setChecked(false);
    }
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(ui->checkBox_2->isChecked()){
        ui->checkBox->setChecked(false);
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()){
        ui->checkBox_2->setChecked(false);
    }
}

void MainWindow::receiveMessage()
{
    QByteArray data2 = socket->readAll();
    QString data1=data2.data();
    if(data1=="staffNo"){
        QMessageBox::critical(0,"警告","请填写正确的校内人员信息",QMessageBox::Cancel);
    }
    else if(data1=="staffYes"){
        qDebug()<<"校内人员信息正确";
    }
    else if(data1=="dataYes"){
        QMessageBox::information(0,"成功","预约成功",QMessageBox::Ok);
    }
}

