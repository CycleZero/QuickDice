#ifndef QUICKDICE_H
#define QUICKDICE_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <detail.h>
#include <QListWidgetItem>
#include <network.h>

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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_listWidget_itemClicked(QListWidgetItem *item);

    void listitem(QString str,long long sum);
    void listitemOnline(QString str);

    void on_pushButton_3_clicked();

    void on_server_clicked();

    void on_uiTest_clicked();



    void createserver(qint16);
    void onNewconnection();
    void onTimeout();
    void onReadyRead();
    void sendMessage(QString msg);
    void sendMessage(QString msg,QTcpSocket *t);

    void on_client_clicked();

    void recvsocket(client *);

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
