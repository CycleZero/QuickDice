#include "detail.h"
#include "ui_detail.h"
#include "quickdice.h"

detail::detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detail)
{
    ui->setupUi(this);
}

detail::~detail()
{
    delete ui;
}

void detail::recdata(QString data)
{
    QStringList list=data.split(':');
    ui->sum->setText(list[0]);
    ui->out->setText(list[1]);
}
