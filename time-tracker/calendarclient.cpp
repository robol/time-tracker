#include "calendarclient.h"
#include <QDebug>
#include <QtConcurrentRun>
#include <QDesktopServices>
#include <QUrl>

extern "C" {
    #include <glib-object.h>
}


#define TIME_TRACKER_APPLICATION_ID "TIME_TRACKER_APPLICATION"

CalendarClient::CalendarClient(QObject *parent) :
    QObject(parent)
{
    QByteArray APP_NAME_DATA = tr("Google Time Tracker").toLatin1();
    m_authorizer = gdata_client_login_authorizer_new(APP_NAME_DATA.data(), GDATA_TYPE_CALENDAR_SERVICE);

    m_service = NULL;

    // Instantiate the Models that will be used by the UI
    // to make the user choose events and/or calendars.
    m_eventListModel = new EventListModel();
    m_calendarListModel = new CalendarListModel();
}

CalendarClient::~CalendarClient()
{
    delete m_eventListModel;
    delete m_calendarListModel;

    if (m_service)
        g_object_unref (m_service);

    if (m_authorizer)
        g_object_unref (m_authorizer);
}

void
CalendarClient::performAuthentication()
{
    // Get a Byte representation of username and password, since we need
    // const char * to be passed to the libgcal methods.
    QByteArray username_data = m_username.toLatin1();
    QByteArray password_data = m_password.toLatin1();

    GError *error = NULL;
//    char * authentication_uri = gdata_client_login_authorizer_new ()

    gdata_client_login_authorizer_authenticate(m_authorizer, username_data.data(),
                                               password_data.data(), NULL, &error);

    if (error != NULL) {
        qDebug() << "Error while authenticating: " << error->message;
        authenticationFailed();
    }
    else {
        qDebug() << "Successfully connected";
        m_service = gdata_calendar_service_new (GDATA_AUTHORIZER (m_authorizer));
        error = NULL;
        GDataFeed *calendars = gdata_calendar_service_query_all_calendars (m_service, NULL, NULL, NULL, NULL, &error);

        if (error) {
            qDebug() << "Error while fetching calendar list: " << error->message;
        }

        m_calendarListModel->setCalendarList(calendars);
        g_object_unref (calendars);

        connected();
    }
}

void
CalendarClient::setAuthenticationData(QString username, QString password)
{
    m_username = username;
    m_password = password;

    QtConcurrent::run(this, &CalendarClient::performAuthentication);
}

EventListModel*
CalendarClient::getEventsModel()
{
//    gdata_calendar_service_query_events(m_service, m_calendarListModel->getCalendar())
//    m_eventListModel->setEventsArray(&m_events);

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
    loadingEventStarted();
//    gcal_get_events(m_client, &m_events);
//    m_eventListModel->setEventsArray(&m_events);
    loadingEventsFinished();
}
