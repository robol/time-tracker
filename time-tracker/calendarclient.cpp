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
    m_activeCalendar = NULL;
    m_eventListModel = new EventListModel();
    m_calendarListModel = new CalendarListModel();

    // When the user logins we need to refresh the list of calendars
    connect(&m_oauth2, SIGNAL(loginDone()), this, SLOT(onLoginDone()));

    // Connect callbacks on data changed signals of the CalendarDataManager
    // instance.
    connect(&m_calendarDataManager, SIGNAL(calendarListReady()), this, SLOT(reloadCalendarList()));
    connect(&m_calendarDataManager, SIGNAL(eventsReady()), this, SLOT(reloadEventList()));

    connect(&m_oauth2, SIGNAL(loginHandlerRequired(QUrl)), this, SLOT(oauth2LoginHandlerRequired(QUrl)));
}

CalendarClient::~CalendarClient()
{
    delete m_eventListModel;
    delete m_calendarListModel;
}

void
CalendarClient::oauth2LoginHandlerRequired(QUrl url)
{
    emit loginHandlerRequired(url);
}

void
CalendarClient::setAuthorizationToken(QString token)
{
    m_oauth2.authorizationTokenObtained(token);
}

void
CalendarClient::clearToken()
{
    m_activeCalendar = NULL;

    qDebug() << "Clearing Token";
    m_eventListModel->clearEvents();
    qDebug() <<  "Cleared events";
    m_calendarListModel->setCalendarList(QList<Calendar*>());

    m_oauth2.clearToken();
    qDebug() << "Token cleared";
}

void
CalendarClient::onLoginDone()
{
    m_calendarDataManager.getCalendars(m_oauth2.accessToken());
    connected();
}

void
CalendarClient::reloadCalendarList()
{
    QVariantList calendars = m_calendarDataManager.getCalendars();
    QVariant calendar;
    QList<Calendar*> calendarList;
    foreach (calendar, calendars) {
        calendarList.append(new Calendar(this, calendar.toMap()));
    }

    m_calendarListModel->setCalendarList(calendarList);
}

void
CalendarClient::performAuthentication()
{
    m_oauth2.startLogin(false);
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
    if (index < 0 || index >= m_calendarListModel->rowCount(QModelIndex()))
        return;
    m_activeCalendar = m_calendarListModel->getCalendar(index);
    reloadEvents();
}

void
CalendarClient::reloadEventList()
{
    QVariantList events = m_calendarDataManager.getEvents();
    QVariant event;
    QList<CalendarEvent*> eventList;
    foreach (event, events) {
        eventList.append (new CalendarEvent (this, event.toMap()));
    }

    m_eventListModel->setEventList(eventList);

    loadingEventsFinished();
}

void
CalendarClient::reloadEvents()
{
    if (!m_activeCalendar) {
        qDebug() << "Refusing to update events since no Calendar is selected";
        return;
    }

    loadingEventsStarted();

    // Clear the events that were already in the Model.
    m_eventListModel->clearEvents();
    m_calendarDataManager.getEventsForCalendar(m_oauth2.accessToken(), m_activeCalendar->getId());
}
