#ifndef CONNECTTO_H
#define CONNECTTO_H

#include <QDialog>
#include <QMessageBox>
#include <network.h>

namespace Ui {
class connectTo;
}

class connectTo : public QDialog
{
    Q_OBJECT

public:
    explicit connectTo(QWidget *parent = nullptr);
    ~connectTo();

private slots:
    void on_connect_clicked();
//    void recvsockets(newserverb *);
//    void recvsocketc(client *);
    void on_servernew_clicked();

signals:
    void sendsocket(client *);
    void sendsocket(newserverb *);

private:
    Ui::connectTo *ui;
};

#endif // CONNECTTO_H
