#include "quickdice.h"
#include "ui_quickdice.h"
#include "newserver.h"
#include "connectto.h"
#include "testwindow.h"


int a[120]={0},b=0;
QString num,fanwei;
newserverb *server;
client *clientb;
bool clientStatus=0,serverStatus=0;
int numclient=0;

QuickDice::QuickDice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuickDice)
{
    ui->setupUi(this);
}

QuickDice::~QuickDice()
{
    delete ui;
}

void QuickDice::on_pushButton_clicked()
{
    long long sum=0;
    QString t;
    QString str=ui->textEdit->toPlainText();
    if(!QString(str).isEmpty())
    {
            ui->out->setText(srec(str,sum));
            ui->sum->setText(t=QString::number(sum));
            listitem(ui->out->toPlainText(),sum);
            if(clientStatus==1)
            {
                QString msg=QString(clientb->username+":"+QString::number(sum)+":"+ui->out->toPlainText());
                clientb->tcpSocket.write(msg.toUtf8());
            }
            if(serverStatus==1)
            {
                QString msg=QString(server->username+":"+QString::number(sum)+":"+ui->out->toPlainText());
               // QByteArray msgb=msg.toLatin1();
                sendMessage(msg);
                qDebug()<<"sendmessage";
            }
            ui->status->setText("状态：完毕");
    }
    else {
            num=ui->counts->toPlainText();
            fanwei=ui->range->toPlainText();
            if(QString(num).isEmpty()||QString(fanwei).isEmpty())
            {
                ui->status->setText("状态：存在空项");
            }
            else {
                int i=1,f=fanwei.toInt(),g=num.toInt();
                QString o="";
                long long b=0;
                int a;
                for(i=1;i<=g;i++)
                {
                    a=QRandomGenerator::global()->bounded(f)+1;
                    o+=QString::number(a);
                    o+=" ";
                    b+=a;
                }
                ui->out->setText(o);
                ui->sum->setText(QString::number(b));
                listitem(o,b);
                if(clientStatus==1)
                {
                    QString msg=QString(clientb->username+":"+QString::number(b)+":"+ui->out->toPlainText());
                    clientb->tcpSocket.write(msg.toUtf8());
                }
                if(serverStatus==1)
                {
                    QString msg=QString(server->username+":"+QString::number(b)+":"+ui->out->toPlainText());
                    sendMessage(msg.toLatin1());
                }
                ui->status->setText("状态：完毕");

            }
    }

}

void QuickDice::on_clean2_clicked()
{
    ui->counts->clear();
    ui->range->clear();
    ui->status->setText("状态：已清空");
}
void QuickDice::on_clean1_clicked()
{
    ui->textEdit->clear();
    ui->status->setText("状态：已清空");
}
void QuickDice::on_copy_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    clip->setText(QString(ui->out->toPlainText()));
    ui->status->setText("已复制");
}


QString QuickDice::rec(QString str,long long &sum)
{
    int num=1,fan=1;
    /*
    int t1=str.indexOf("r");
    int t2=str.indexOf("d");
    if(t1!=-1)
    {
        if(t2!=-1)
        {
            QString t3=str.mid(t1+1,t2-t1-1);
            QString t4=str.mid(t2+1);
            num=t3.toInt();
            fan=t4.toInt();
        }
        else {
            return "!";
        }
    }
    else {
        if(t2!=-1)
        {
            QString t4=str.mid(t2+1);
            fan=t4.toInt();
        }
        else {
            sum+=str.toInt();
            return str+" ";
        }

    }
    */
    int t1=str.indexOf("d");
    if(t1!=-1)
    {
        QStringList list=str.split('d');
        if(!list[0].isEmpty())
        {
            num=list[0].toInt();
        }
        if(!list[1].isEmpty())
        {
            fan=list[1].toInt();
        }

    }
    else {
        sum+=str.toInt();
        return str+" ";
    }
    int a,i;
    QString o="";
    for(i=1;i<=num;i++)
    {
        a=QRandomGenerator::global()->bounded(fan)+1;
        sum+=a;
        o+=QString::number(a);
        o+=" ";
    }
    return o;
}

QString QuickDice::srec(QString str,long long &sum)
{
    sum=0;
    QStringList list=str.split('+');
    int i;
    QString o="";
    QString tmp;
    for(i=0;i<list.size();i++)
    {
        tmp=rec(list[i],sum);
        if(tmp=="!")
        {
            sum=0;
            return "Error";
        }
        o+=tmp;
    }
    return o;
}

void QuickDice::listitem(QString str,long long sum)
{
    QListWidgetItem *item=new QListWidgetItem();
    item->setSizeHint(QSize(ui->listWidget->width(),20));
    item->setText(QString(QString::number(sum)+":"+str));
    item->setFlags(Qt::ItemIsEnabled);
    ui->listWidget->addItem(item);
}

void QuickDice::listitemOnline(QString str)
{
    QListWidgetItem *item=new QListWidgetItem();
    item->setSizeHint(QSize(ui->listWidget->width(),20));
    item->setText(QString(str));
    item->setFlags(Qt::ItemIsEnabled);
    ui->listWidget->addItem(item);
}


void QuickDice::on_listWidget_itemClicked(QListWidgetItem *item)
{
    detail *t=new detail();
    connect(this,SIGNAL(senddata(QString)),t,SLOT(recdata(QString)));
    emit senddata(item->text());
    t->show();
}








//-------------------------Server----------------------------





void QuickDice::recvsocket(newserverb *s)
{
    server=s;
    if(server->server.listen(QHostAddress::Any,server->port) == false)
    {
        qDebug() << "服务器创建失败!";
        return;
    }
    serverStatus=1;
    qDebug() << "服务器创建成功!";

    connect(&server->server,SIGNAL(newConnection()),this,SLOT(onNewconnection()));
    ui->status->setText("服务器已启动");

    //禁用创建服务器按钮和端口的输入
 //   ui->server->setEnabled(false);
   // ui->client->setEnabled(false);

       //定时器到时发送timeout信号,连接定时器处理的槽函数
    connect(&server->timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
        //开始定时器,每隔3秒时间检查一次容器中是否存在断开连接的套接字
    server->timer.start(3000);

}



void QuickDice::onNewconnection()
{
    QTcpSocket* clientl =  server->server.nextPendingConnection();

    server->tcpClientList.append(clientl);
    numclient++;
    ui->status->setText(QString("当前连接："+QString::number(numclient)));
    connect(clientl,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

void QuickDice::onReadyRead()
{
    for(int i=0;i<server->tcpClientList.size();i++)
    {
        if(server->tcpClientList.at(i)->bytesAvailable())
        {
            QByteArray buf = server->tcpClientList.at(i)->readAll();
            QTcpSocket *t;
            t=server->tcpClientList[i];
            listitemOnline(QString(buf));
qDebug()<<"server recv";
            sendMessage(buf,t);
        }
    }
}


void QuickDice::sendMessage(QString msg)
{
    for(int i=0;i<server->tcpClientList.size();i++)
    {
        if(server->tcpClientList.at(i)->write(msg.toUtf8())<=0)
        {
            qDebug()<<"send error";
        }

    }
}
void QuickDice::sendMessage(QString msg,QTcpSocket *t)
{
    for(int i=0;i<server->tcpClientList.size();i++)
    {
        if(server->tcpClientList[i]!=t)
        {
            if(server->tcpClientList.at(i)->write(msg.toUtf8())<=0)
            {
                qDebug()<<"send error";
            }
        }

    }
}

void QuickDice::onTimeout()
{
    for(int i=0;i<server->tcpClientList.size();i++)
    {
        if(server->tcpClientList.at(i)->state()==QAbstractSocket::UnconnectedState)
        {
            server->tcpClientList.removeAt(i);
            --i;
            numclient--;
            ui->status->setText(QString("当前连接："+QString::number(numclient)));
        }
    }
}


void QuickDice::serveroff()
{
    serverStatus=0;
    ui->status->setText("服务器已关闭");
}


//--------------------------------Client----------------------



void QuickDice::on_net_clicked()
{
    if(clientStatus==0&&serverStatus==0)
    {
        connectTo *cu=new connectTo();
        connect(cu,SIGNAL(sendsocket(client *)),this,SLOT(recvsocket(client *)));
        connect(cu,SIGNAL(sendsocket(newserverb *)),this,SLOT(recvsocket(newserverb *)));
        cu->show();
    }
    else {
        if(serverStatus==1)
        {
            OnServer *ss=new OnServer();
            connect(ss,SIGNAL(serverclosed()),this,SLOT(serveroff()));
            connect(this,SIGNAL(sendsocket(newserverb *)),ss,SLOT(recvsocket(newserverb *)));
            emit sendsocket(server);
            ss->show();
        }
    }

}

void QuickDice::recvsocket(client *c)
{
    clientb=c;
    connect(&clientb->tcpSocket,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(&clientb->tcpSocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    connect(&clientb->tcpSocket,SIGNAL(readyRead()),this,SLOT(onReadRead()));
    connect(&clientb->tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError()));
    clientb->tcpSocket.connectToHost(c->serverIp,c->serverPort);
}


void QuickDice::onConnected()
{
    clientStatus=1;
    numclient++;
    ui->status->setText(QString("当前连接："+QString::number(numclient)));

}

void QuickDice::onDisconnected()
{
    clientStatus=0;
    numclient--;
    ui->status->setText(QString("当前连接："+QString::number(numclient)));


}

void QuickDice::onReadRead()
{
    qDebug()<<"onreadyRead";
    if(clientb->tcpSocket.bytesAvailable())
    {
            //读取消息
        qDebug()<<"client recv";
    QByteArray buf = clientb->tcpSocket.readAll();
            //显示消息到界面
    listitemOnline(QString(buf));
    }
}

void QuickDice::onError()
{
    QMessageBox::critical(this,"Error",clientb->tcpSocket.errorString());
}


