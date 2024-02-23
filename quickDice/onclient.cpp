#include "onclient.h"
#include "ui_onclient.h"

OnClient::OnClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnClient)
{
    ui->setupUi(this);
}

OnClient::~OnClient()
{
    delete ui;
}

void OnClient::on_connectoff_clicked()
{
    op_client->tcpSocket.close();
}

void OnClient::recvsocket(client *c)
{
    op_client=c;
    ui->textEdit->setText(QString("已连接："+op_client->serverIp.toString()+":"+op_client->serverPort));
}
