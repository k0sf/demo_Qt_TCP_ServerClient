#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("server");

    // 服务器参数初始化
    server=new QTcpServer();
    connect(server,&QTcpServer::newConnection,[=](){
        server_New_Connect();
    });
    ui->lineEdit_IP->setText("192.168.1.4");
    ui->lineEdit_Port->setText("6666");

}

MainWindow::~MainWindow()
{
    server->close();
    server->deleteLater();
    delete ui;
}


void MainWindow::on_pushButton_Listen_clicked()
{
    // 监听一个端口，客户端可以使用这个端口访问服务器
    QHostAddress IP(ui->lineEdit_IP->text());
    quint16 port=ui->lineEdit_Port->text().toInt();
    if(server->listen(IP,port)){
        QMessageBox::warning(this,"成功","监听成功");
    }else{// 监听失败
        QMessageBox::warning(this,"失败","监听失败!!!");
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
        QMessageBox::warning(this,"成功",tr("写数据成功  %1").arg(writeResult));
    }
}

void MainWindow::server_New_Connect(){
    socket = server->nextPendingConnection();
    connect(socket,&QTcpSocket::readyRead,[=](){
        socket_Read_Data();
    });
    connect(socket,&QTcpSocket::disconnected,[=](){
        socket_Disconnect();
    });
}
void MainWindow::socket_Read_Data(){
    QByteArray buffer;
    buffer=socket->readAll();
    ui->textEdit_Receive->setText(buffer);
}
void MainWindow::socket_Disconnect(){

}
