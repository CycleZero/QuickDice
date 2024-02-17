#include "connectto.h"
#include "ui_connectto.h"



connectTo::connectTo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectTo)
{
    ui->setupUi(this);
}

connectTo::~connectTo()
{
    delete ui;
}

void connectTo::on_connect_clicked()
{
    client *c=new client();
    if(c->serverIp.setAddress(ui->IP->text())==false)
    {
        QMessageBox::critical(this,"Error","IP地址格式错误!");
        return;
    }
    c->serverPort = ui->Port->text().toShort();
    if(c->serverPort < 1024)
    {
        QMessageBox::critical(this,"Error","端口格式错误!");
        return;
    }
    c->username=ui->Username->text();
    if(c->username=="")
    {
        QMessageBox::critical(this,"Error","用户名不能为空!");
        return;
    }

    emit sendsocket(c);
    this->close();
}
