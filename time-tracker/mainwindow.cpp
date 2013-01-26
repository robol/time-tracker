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
    authenticated();
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
    matcher.setStartDate(ui->startCalendarWidget->selectedDate());
    matcher.setEndDate(ui->endCalendarWidget->selectedDate());

    // Test code to show that we are really able to parse the Events
    long long int totalMinutes = 0;
    int events = 0;
    for(int i = 0; i < model->rowCount(QModelIndex()); i++)
    {
        CalendarEvent* event = model->getEventAt(i);
        if (matcher.match(*event))
        {
            totalMinutes += int(60 * event->getDuration());
            events += 1;
            qDebug() << "Matching event found:" << event->getTitle() << " // Duration:"
                     << event->getDuration();
        }
        else
            qDebug() << "Non-matching event found:" << event->getTitle();
    }

    // Display the total number of hours in a clean way
    QMessageBox mBox(this);
    mBox.setIcon(QMessageBox::Information);
    mBox.setInformativeText(tr("<html><strong>%1</strong> events match the given pattern.<br />"
                               "These accounts for a total of <strong>%2</strong> hours.</html>").
                            arg(events).arg(totalMinutes / 60));
    mBox.setText(tr("<html><strong>%1 hours matching the given pattern</strong></html>").arg(totalMinutes / 60));
    mBox.setWindowTitle(tr("Computation completed"));
    mBox.exec();
}

void MainWindow::on_actionDisconnect_triggered()
{
    m_client->clearToken();
    startAuthentication();
}

void MainWindow::startAuthentication()
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
