#ifndef ONCLIENT_H
#define ONCLIENT_H

#include <QDialog>
#include <network.h>

namespace Ui {
class OnClient;
}

class OnClient : public QDialog
{
    Q_OBJECT

public:
    explicit OnClient(QWidget *parent = nullptr);
    ~OnClient();

private slots:
    void on_connectoff_clicked();
    void recvsocket(client *);


private:
    Ui::OnClient *ui;
    client * op_client;
};

#endif // ONCLIENT_H
