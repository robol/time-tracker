#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendarclient.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_client = new CalendarClient();
    ui->setupUi(this);

    // Set the PushButton for the computation of the hours
    // as inactive until the connection is established.
    ui->computeButton->setDisabled(true);

    // Connect callbacks
    QObject::connect(m_client, SIGNAL(connected()), this, SLOT(onClientConnected()));
    QObject::connect(m_client, SIGNAL(authenticationFailed()), this, SLOT(onAuthenticationFailed()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_client;
}

void
MainWindow::onClientConnected()
{
    ui->computeButton->setDisabled(false);
}

void MainWindow::onAuthenticationFailed()
{
    QMessageBox box;
    box.setIcon(QMessageBox::Critical);
    box.setText(tr("Authentication on Google calendar failed."));
    box.setInformativeText(tr("Please check your username and password."));
    box.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    m_client->setAuthenticationData(ui->usernameLineEdit->text(),
                                    ui->passwordLineEdit->text());
}

void MainWindow::on_computeButton_clicked()
{
    qDebug() << "Starting to compute the total time used for the tasks";

    EventListModel* model = m_client->getEventsModel();

    for(int i = 0; i < model->rowCount(QModelIndex()); i++)
    {
        gcal_event_t event = model->getEventAt(i);
        qDebug() << "Event = " << gcal_event_get_title(event);
    }
}
