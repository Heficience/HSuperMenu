 
#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/Images/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();

    QCoreApplication::setOrganizationName("Heficience");
    QCoreApplication::setOrganizationDomain("https://www.heficience.com/");
    QCoreApplication::setApplicationName("hsupermenu");

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.showNormal();

    splash.finish(&w);
    return a.exec();
}
