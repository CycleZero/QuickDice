#ifndef NEWSERVER_H
#define NEWSERVER_H

#include <QDialog>

namespace Ui {
class newServer;
}

class newServer : public QDialog
{
    Q_OBJECT

public:
    explicit newServer(QWidget *parent = nullptr);
    ~newServer();

private slots:
    void on_servernew_clicked();
signals:
    void newserver(qint16);


private:
    Ui::newServer *ui;
};

#endif // NEWSERVER_H
