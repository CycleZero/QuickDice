#ifndef QUICKDICE_H
#define QUICKDICE_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <detail.h>
#include <QListWidgetItem>
#include <network.h>
#include <QClipboard>
#include <onserver.h>
#include <onclient.h>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QRect>

namespace Ui {
class QuickDice;

}

class QuickDice : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(double bcolor READ bcolor WRITE setBcolor)


public:
    explicit QuickDice(QWidget *parent = nullptr);
    ~QuickDice();
    QString rec(QString str,long long &sum);
    QString srec(QString str,long long &sum);
    double bcolor()const;
    void setBcolor(double bcolor);

signals:
    void senddata(QString);
    void sendsocket(client *);
    void sendsocket(newserverb *);
    void sendanivar(double);

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

    //------------UI-----------

    void buttonColorChange(double sv,double ev);
    void recvanivar(double);
    void btnanifin();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::QuickDice *ui;

    QPropertyAnimation *m_animation;
    double m_bcolor;
    QPushButton *currentchange;


};


#endif // QUICKDICE_H
