#include "calendarclient.h"
#include <QDebug>
#include <QtConcurrentRun>
#include <QDesktopServices>
#include <QUrl>

#define TIME_TRACKER_APPLICATION_ID "TIME_TRACKER_APPLICATION"

CalendarClient::CalendarClient(QObject *parent) :
    QObject(parent)
{
    QByteArray APP_NAME_DATA = tr("Google Time Tracker").toLatin1();

    // Instantiate the Models that will be used by the UI
    // to make the user choose events and/or calendars.
    m_eventListModel = new EventListModel();
    m_calendarListModel = new CalendarListModel();
}

CalendarClient::~CalendarClient()
{
    delete m_eventListModel;
    delete m_calendarListModel;
}

void
CalendarClient::performAuthentication()
{
    m_oauth2.startLogin(true);
}

EventListModel*
CalendarClient::getEventsModel()
{
    return m_eventListModel;
}

CalendarListModel*
CalendarClient::getCalendarsModel()
{
    return m_calendarListModel;
}

void
CalendarClient::selectCalendar(int index)
{
//    m_client = m_calendarListModel->getCalendar(index);
    QtConcurrent::run(this, &CalendarClient::reloadEvents);
}

void
CalendarClient::reloadEvents()
{
    loadingEventsStarted();

    m_eventListModel->clearEvents();

    loadingEventsFinished();
}
