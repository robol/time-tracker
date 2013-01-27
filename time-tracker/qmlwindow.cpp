#include "qmlwindow.h"
#include "ui_qmlwindow.h"

QmlWindow::QmlWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QmlWindow)
{
    ui->setupUi(this);
    ui->declarativeView->setSource(QUrl("qrc:/qml/Calendar.qml"));
}

QmlWindow::~QmlWindow()
{
    delete ui;
}

void
QmlWindow::startAuthentication()
{

}
