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
    if(list.size()==2)
    {
        ui->sum->setText(list[0]);
        ui->out->setText(list[1]);
    }
    else {
        ui->sum->setText(list[1]);
        ui->out->setText(list[2]);
    }

}
