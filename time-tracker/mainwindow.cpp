#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendarclient.h"
#include "eventmatcher.h"
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
    QObject::connect(m_client, SIGNAL(loadingEventsStarted()), this, SLOT(clientLoadingEventsStarted()));
    QObject::connect(m_client, SIGNAL(loadingEventsFinished()), this, SLOT(clientLoadingEventsFinished()));

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
    EventMatcher matcher(ui->queryLineEdit->text());

    // Test code to show that we are really able to parse the Events
    long long int totalHours = 0;
    for(int i = 0; i < model->rowCount(QModelIndex()); i++)
    {
        CalendarEvent* event = model->getEventAt(i);
        if (matcher.match(*event)) {
            totalHours += int(event->getDuration());
            qDebug() << "Matching event found:" << event->getTitle() << " // Duration:"
                     << event->getDuration();
        }
        else
            qDebug() << "Non-matching event found:" << event->getTitle();
    }

    qDebug() << "Total hours =" << totalHours;
}

void MainWindow::on_connectPushButton_clicked()
{
    m_client->performAuthentication();
}

void MainWindow::on_calendarComboBox_currentIndexChanged(int index)
{
    m_client->selectCalendar(index);
}

void MainWindow::clientLoadingEventsStarted()
{
    ui->statusBar->showMessage(tr("Downloading events..."));
}

void MainWindow::clientLoadingEventsFinished()
{
    ui->statusBar->showMessage(tr("Downloading events completed"));
    ui->computeButton->setDisabled(false);
}
