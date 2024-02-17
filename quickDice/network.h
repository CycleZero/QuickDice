#ifndef NETWORK_H
#define NETWORK_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QTimer>
#include <QHostAddress>



namespace UI {
class network;
}




class network : public QDialog
{
public:
    network();
};



class newserverb : public QThread
{
    protected:
    volatile bool vstop;
    //void run();

public:

    newserverb();
    //void stop();
    qint16 port;
    QTcpServer server;
    QList<QTcpSocket*> tcpClientList;
    QTimer timer;
    QString username;

private slots:
    void onNewconnection();
    void onTimeout();
    void onReadyRead();
    void sendMessage(const QByteArray& msg);


};



class client
{
private slots:
    //void on_sendButton_clicked();
        //连接服务器按钮对应的槽函数
   // void on_connectButton_clicked();
        //和服务器连接成功时执行的槽函数
    //void onConnected();
        //和服务器断开连接时执行的槽函数
    //void onDisconnected();
        //接收聊天消息的槽函数
   // void onReadRead();
        //网络异常是执行的槽函数
public:
    bool status;//标记客户端状态,true:在线状态,false:离线状态
    QTcpSocket tcpSocket;//和服务器通信的TCP的套接字
    QHostAddress serverIp;//服务器的IP
    quint16 serverPort;//服务器端口
    QString username;//聊天室昵称

};

#endif // NETWORK_H
