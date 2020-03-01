#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    socket = new QTcpSocket();// 初始化客户端
    connect(socket,&QTcpSocket::readyRead,[=](){
        socket_Read_Data();
    });
    ui->lineEdit_IP->setText("192.168.1.4");
    ui->lineEdit_Port->setText("6666");
}

MainWindow::~MainWindow()
{
    delete this->socket;// 删除客户端对象
    delete ui;
}


void MainWindow::on_pushButton_Listen_clicked()
{
    socket->abort();// 取消已有连接
    socket->connectToHost(ui->lineEdit_IP->text(),ui->lineEdit_Port->text().toInt()); // 连接服务器
    if(!socket->waitForConnected(30000)){
        qDebug()<<"连接服务器失败，请重新操作!!!";
    }else{
        qDebug()<<"连接服务器成功！";
        QMessageBox::warning(this,"连接提示","连接成功 Yes");
    }

}

void MainWindow::on_pushButton_Send_clicked()
{
    qint64 writeResult = socket->write(ui->textEdit_Send->toPlainText().toLatin1());// 发送socket数据包
    bool BoolFlush = socket->flush();// 从缓冲区读写数据，如果从缓冲区读写了数据，则返回true。否则false。
    if(writeResult != -1 && BoolFlush == 1){
        if(writeResult == 0){
            QMessageBox::warning(this,"成功","写数据结果返回值为0");
        }
        QMessageBox::warning(this,"成功",tr("写数据成功 %1").arg(writeResult));
    }
}

void MainWindow::socket_Read_Data(){
    QByteArray buffer;
    buffer=socket->readAll();

    ui->textEdit_Receive->setText(buffer);
}
void MainWindow::socket_Disconnect(){

}
