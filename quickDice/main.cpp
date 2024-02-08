#include "quickdice.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    qputenv("QT_SCALE_FACTOR", "2.0");


    QApplication a(argc, argv);
    QuickDice w;
    w.show();

    return a.exec();
}
