#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.connect(&w, SIGNAL(authenticated()), &w, SLOT(show()));
    w.startAuthentication();
    
    return a.exec();
}
