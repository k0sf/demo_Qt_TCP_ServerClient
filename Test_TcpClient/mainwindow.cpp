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

    ui->lineEdit_IP->setText("127.0.0.1");
    ui->lineEdit_Port->setText("9000");
}

MainWindow::~MainWindow()
{
    delete this->socket;// 删除客户端对象
    delete ui;
}


void MainWindow::on_pushButton_Listen_clicked()
{
    socket->abort();// 取消已有连接
    // 绑定本地固定端口
//    if(socket->bind(QHostAddress::LocalHost, 50001)){
//        qDebug()<<"绑定本地端口成功";
//        QMessageBox::information(this,"连接提示","绑定本地端口成功");
//    }else{
//        qDebug()<<"绑定本地端口失败！！！";
//        QMessageBox::warning(this,"成功",tr("绑定本地端口失败！！！"));
//    }
//    socket->localAddress().toString();// 本地地址
//    socket->localPort();// 本地端口
    // 连接到主机
    socket->connectToHost(ui->lineEdit_IP->text(),ui->lineEdit_Port->text().toInt()); // 连接服务器
    if(!socket->waitForConnected(30000)){
        qDebug()<<"连接服务器失败，请重新操作!!!";
        QMessageBox::warning(this,"连接提示","连接失败 No");
    }else{
        qDebug()<<"连接服务器成功！";
        QMessageBox::information(this,"连接提示","连接成功 Yes");
    }

}

void MainWindow::on_pushButton_Send_clicked()
{
    qint64 writeResult = socket->write(ui->textEdit_Send->toPlainText().toLocal8Bit());// 发送socket数据包
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

    ui->textEdit_Receive->setText(QString::fromLocal8Bit(buffer));
}
void MainWindow::socket_Disconnect(){
//    socket->disconnect();
}
