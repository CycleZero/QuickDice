#include "onserver.h"
#include "ui_onserver.h"

OnServer::OnServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnServer)
{
    ui->setupUi(this);
}

OnServer::~OnServer()
{
    delete ui;
}

void OnServer::on_serveroff_clicked()
{
    op_server->server.close();
    emit serverclosed();
    qDebug()<<"关闭服务器";
    this->close();
}

void OnServer::recvsocket(newserverb * s)
{
    op_server=s;
    qDebug()<<"接收到socket";
    for(int i=0;i<op_server->tcpClientList.size();i++)
    {
        QListWidgetItem *item=new QListWidgetItem();
        item->setSizeHint(QSize(ui->clientslist->width(),20));
        item->setText(QString(op_server->tcpClientList.at(i)->peerAddress().toString()+":"+op_server->tcpClientList.at(i)->peerPort()));
        item->setFlags(Qt::ItemIsEnabled);
        ui->clientslist->addItem(item);

    }
}
