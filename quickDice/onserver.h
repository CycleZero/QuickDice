#ifndef ONSERVER_H
#define ONSERVER_H

#include <QDialog>
#include <network.h>

namespace Ui {
class OnServer;
}

class OnServer : public QDialog
{
    Q_OBJECT

public:
    explicit OnServer(QWidget *parent = nullptr);
    ~OnServer();

private slots:
    void on_serveroff_clicked();
    void recvsocket(newserverb *);


signals:
    void serverclosed();
private:
    Ui::OnServer *ui;
    newserverb *op_server  ;
};

#endif // ONSERVER_H
