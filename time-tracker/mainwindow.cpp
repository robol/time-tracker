#define QT_NO_KEYWORDS

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

    // Connect callbacks for the CalendarClient
    QObject::connect(m_client, SIGNAL(connected()), this, SLOT(onClientConnected()));
    QObject::connect(m_client, SIGNAL(authenticationFailed()), this, SLOT(onAuthenticationFailed()));
    QObject::connect(m_client, SIGNAL(loadingEventStarted()), this, SLOT(on_clientLoadingEventsStarted()));
    QObject::connect(m_client, SIGNAL(loadingEventsFinished()), this, SLOT(on_clientLoadingEventsFinished()));

    // Get the calendar model and set it in the ComboBox
    ui->calendarComboBox->setModel(m_client->getCalendarsModel());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_client;
}

void
MainWindow::onClientConnected()
{
    ui->statusBar->showMessage(tr("Connected to Google Calendar"));
    ui->computeButton->setDisabled(false);
}

void MainWindow::onAuthenticationFailed()
{
    QMessageBox box;

    ui->statusBar->showMessage(tr("Authentication failed"));

    box.setIcon(QMessageBox::Critical);
    box.setText(tr("Authentication on Google calendar failed."));
    box.setInformativeText(tr("Please check your username and password."));
    box.exec();
}

void MainWindow::on_computeButton_clicked()
{
    qDebug() << "Starting to compute the total time used for the tasks";

    EventListModel* model = m_client->getEventsModel();

    // Test code to show that we are really able to parse the Events
    for(int i = 0; i < model->rowCount(QModelIndex()); i++)
    {
        CalendarEvent* event = model->getEventAt(i);
        // qDebug() << "Event = " << event->getTitle() << " Duration = " << event->getDuration();
        delete event;
    }
}

void MainWindow::on_connectPushButton_clicked()
{
    m_client->setAuthenticationData(ui->usernameLineEdit->text(),
                                    ui->passwordLineEdit->text());
}

void MainWindow::on_calendarComboBox_currentIndexChanged(int index)
{
    m_client->selectCalendar(index);
}

void MainWindow::on_clientLoadingEventsStarted()
{
    ui->statusBar->showMessage(tr("Downloading events..."));
}

void MainWindow::on_clientLoadingEventsFinished()
{
    ui->statusBar->showMessage(tr("Downloading events completed"));
}
