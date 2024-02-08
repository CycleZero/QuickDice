#include "quickdice.h"
#include "ui_quickdice.h"

int a[120]={0},b=0;
QString num,fanwei;

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
                ui->status->setText("状态：完毕");

            }
    }

}

void QuickDice::on_pushButton_2_clicked()
{
    ui->out->clear();
    ui->status->setText("状态：已清空");
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


void QuickDice::on_listWidget_itemClicked(QListWidgetItem *item)
{
    detail *t=new detail();
    connect(this,SIGNAL(senddata(QString)),t,SLOT(recdata(QString)));
    emit senddata(item->text());
    t->show();
}




void QuickDice::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
}
