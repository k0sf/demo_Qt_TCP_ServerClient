#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void socket_Read_Data();// 服务器读客户端传输过来的数据
    void socket_Disconnect();// 断开服务器与客户端连接槽函数
private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket *socket;// 创建客户端对象
};
#endif // MAINWINDOW_H
