#include <QApplication>

#ifdef TIMETRACKER_DESKTOP
#include "mainwindow.h"
#else
#include "qmlwindow.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef TIMETRACKER_DESKTOP
      MainWindow w;
#else
    QmlWindow w;
#endif

    w.show();
    w.startAuthentication();

    return a.exec();
}
