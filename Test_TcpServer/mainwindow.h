#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void server_New_Connect();// 服务器接收到客户端消息信号，触发连接槽函数（连接客户端）
    void socket_Read_Data();// 服务器读客户端传输过来的数据
    void socket_Disconnect();// 断开服务器与客户端连接槽函数
private slots:

    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();



private:
    Ui::MainWindow *ui;

    QTcpServer *server;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
