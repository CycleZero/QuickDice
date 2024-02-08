#ifndef QUICKDICE_H
#define QUICKDICE_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <detail.h>
#include <QListWidgetItem>

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

    void on_pushButton_3_clicked();

private:
    Ui::QuickDice *ui;
};

#endif // QUICKDICE_H
