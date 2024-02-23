#ifndef QUICKDICE_H
#define QUICKDICE_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <detail.h>
#include <QListWidgetItem>
#include <network.h>
#include <QClipboard>
#include <onserver.h>

namespace Ui {
class QuickDice;

}

class QuickDice : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuickDice(QWidget *parent = nullptr);
    ~QuickDice();
    QString rec(QString str,long long &sum);
    QString srec(QString str,long long &sum);

signals:
    void senddata(QString);
    void sendsocket(client *);
    void sendsocket(newserverb *);

private slots:
    void on_pushButton_clicked();

    void on_clean2_clicked();
    void on_clean1_clicked();
    void on_copy_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void listitem(QString str,long long sum);
    void listitemOnline(QString str);



    void on_net_clicked();






    void onNewconnection();
    void onTimeout();
    void onReadyRead();
    void sendMessage(QString msg);
    void sendMessage(QString msg,QTcpSocket *t);


    void recvsocket(client *);
    void recvsocket(newserverb *);

    void serveroff();

   // void on_sendButton_clicked();
        //连接服务器按钮对应的槽函数
    //void on_connectButton_clicked();
        //和服务器连接成功时执行的槽函数
    void onConnected();
        //和服务器断开连接时执行的槽函数
    void onDisconnected();
        //接收聊天消息的槽函数
    void onReadRead();
    void onError();

private:
    Ui::QuickDice *ui;
};


#endif // QUICKDICE_H
