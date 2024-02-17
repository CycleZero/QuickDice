#include "newserver.h"
#include "ui_newserver.h"
#include "network.h"


newServer::newServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newServer)
{
    ui->setupUi(this);
}

newServer::~newServer()
{
    delete ui;
}

void newServer::on_servernew_clicked()
{
    emit newserver(ui->port->text().toShort());

    this->close();
}

