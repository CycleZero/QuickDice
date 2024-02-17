#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <QListWidgetItem>
#include <winsock2.h>

namespace Ui {
class detail;
}

class detail : public QWidget
{
    Q_OBJECT

public:
    explicit detail(QWidget *parent = nullptr);
    ~detail();

private slots:
    void recdata(QString);

private:
    Ui::detail *ui;
};

#endif // DETAIL_H
