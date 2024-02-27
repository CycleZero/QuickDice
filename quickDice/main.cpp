#include "quickdice.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

   // qputenv("QT_SCALE_FACTOR", "2.0");

    //这个是Windows平台用来获取屏幕宽度的代码，
        //因为在qApplication实例初始化之前，QGuiApplication::screens();无法使用。
    DEVMODE NewDevMode;
        //获取屏幕设置中的分辨率
        EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);
        qreal  cx = NewDevMode.dmPelsWidth;
    qreal scale = cx / 2560;				// 960 = 1920 / 2

    qputenv("QT_SCALE_FACTOR", QString::number(scale).toLatin1());

    QApplication a(argc, argv);
    QuickDice w;
    w.show();

    return a.exec();
}
