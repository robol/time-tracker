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
    m_authorizer = gdata_oauth1_authorizer_new (APP_NAME_DATA.data(),
                                                GDATA_TYPE_CALENDAR_SERVICE);

    m_token = m_token_secret = NULL;

    char * authentication_uri = gdata_oauth1_authorizer_request_authentication_uri (m_authorizer,
                                                                                    &m_token, &m_token_secret,
                                                                                    NULL, NULL);
    qDebug() << "Open URL " << authentication_uri;
    QDesktopServices::openUrl(QUrl(authentication_uri));

    m_service = gdata_calendar_service_new (GDATA_AUTHORIZER (m_authorizer));

    // Instantiate the Models that will be used by the UI
    // to make the user choose events and/or calendars.
    m_eventListModel = new EventListModel();
    m_calendarListModel = new CalendarListModel();
}

CalendarClient::~CalendarClient()
{
    delete m_eventListModel;
    delete m_calendarListModel;

    if (m_token)
        g_free (m_token);
    if (m_token_secret)
    {
        memset (m_token_secret, 0, strlen (m_token_secret));
        g_free (m_token_secret);
    }

    g_object_unref (m_service);
    g_object_unref (m_authorizer);
}

void
CalendarClient::performAuthentication()
{
    // Get a Byte representation of username and password, since we need
    // const char * to be passed to the libgcal methods.
    QByteArray username_data = m_username.toLatin1();
    QByteArray password_data = m_password.toLatin1();

//    // Try to authenticate on Google Calendar, and give a warning if it does
//    // not succeed.
//    int result = gcal_get_authentication(m_client, username_data.data(), password_data.data());
//    if (result != 0)
//    {
//        qDebug() << "Warning: Authentication failed on Google Calendar";
//        authenticationFailed();
//    }
//    else
//    {
//        // Find the list of the calendars that the user have so we can choose
//        // them from the ComboBox.
//        struct gcal_resource_array *resources = new gcal_resource_array;
//        gcal_calendar_list(m_client, resources);

//        m_calendarListModel->setCalendarList(resources);

//        connected();
//    }
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
