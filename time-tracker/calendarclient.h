#define QT_NO_KEYWORDS

#ifndef CALENDARCLIENT_H
#define CALENDARCLIENT_H

#include <QObject>
#include "eventlistmodel.h"
#include "calendarlistmodel.h"

extern "C" {
    #include <gdata/services/calendar/gdata-calendar-service.h>
    #include <gdata/gdata-authorizer.h>
    #include <gdata/gdata-client-login-authorizer.h>
}

/**
 * @brief The CalendarClient class is aimed to provide a simple interface
 * for browsing events in Google Calendars of a specified user.
 */
class CalendarClient : public QObject
{
    Q_OBJECT
public:
    explicit CalendarClient(QObject *parent = 0);
    ~CalendarClient();

    /**
     * @brief setAuthenticationData can be used to select username and
     * password for the authentication step that will be required when
     * connecting to Google Calendar service.
     *
     * Please note that this function is asynchronous and the signals
     * connected() or authenticationFailed() will be emitted
     * based on the result of the authentication process.
     *
     * @param username The username that shall be used for the connection
     * @param password The password that shall be used for the connection
     */
    void setAuthenticationData(QString username, QString password);

    /**
     * @brief getEventsModel returns a Model representing the Events of the
     * user calendars.
     *
     * @return A pointer to the EventListModel* representing the events
     * of the requested calendar.
     */
    EventListModel* getEventsModel();

    /**
     * @brief getCalendarsModel can be used to retrieve a Model representing the
     * current list of the calendars of the connected user, or an empty model
     * if the user is disconnected.
     *
     * @return A pointer to the internal CalendarsListModel. It should not be freed.
     */
    CalendarListModel* getCalendarsModel();

    /**
     * @brief selectCalendar select the active calendar used to retrieve events.
     * @param index must be a positive integer from 0 to the number of calendars loaded,
     * that can be retrieved by the model obtained through getCalendarsModel().
     */
    void selectCalendar(int index);

private:

    /**
     * @brief performAuthentication, as the name suggests, perform the hard work
     * behind the authentication process once that setAuthenticationData() has been called.
     * Please note that a call to the latter routine will automatically trigger a call
     * to performAuthentication in a background thread, so there is no reason for calling
     * this method directly.
     */
    void performAuthentication();

    /**
     * @brief m_username The username provided by the user. Please note that these
     * fields will be deprecated as soon this class is migrated to the user of
     * GDataOAuth1Authorizer.
     */
    QString m_username;

    /**
     * @brief m_password The password provided by the user. Please note that these
     * fields will be deprecated as soon this class is migrated to the user of
     * GDataOAuth1Authorizer.
     */
    QString m_password;

    /**
     * @brief m_service is used to retrieve data from the Google servers.
     */
    GDataCalendarService *m_service;

    // GDataOAuth1Authorizer *m_authorizer;
    /**
     * @brief m_authorizer The authorizer used to perform authentication. While this is
     * now a GDataClientLoginAuthorizer, a migration to the use of GDataOAuth1Authorizer
     * could be evaluted in the future.
     */
    GDataClientLoginAuthorizer *m_authorizer;

    /**
     * @brief m_client is a pointer to the user selected calendar.
     */
    GDataCalendarCalendar *m_client;

    /**
     * @brief m_eventListModel is a model representing the events in the calendar
     * currently selected.
     */
    EventListModel* m_eventListModel;

    /**
     * @brief m_calendarListModel is a model representing the calendars of the user.
     */
    CalendarListModel* m_calendarListModel;

    /**
     * @brief reloadEvents reload asynchronously the events from the currently selected
     * calendar and then set them in the EventsModel.
     */
    void reloadEvents();
    
Q_SIGNALS:
    /**
     * @brief connected signal is emitted when the client authenticates successfuly
     * against Google Calendar.
     */
    void connected();

    /**
     * @brief disconnected signal is emitted when the connection with Google Calendar
     * is terminated.
     */
    void disconnected();

    /**
     * @brief authenticationFailed is the signal emitted after a call to setAuthenticationData
     * that leads to an authentication failed response from Google.
     */
    void authenticationFailed();

    /**
     * @brief loadingEventStarted is emitted when the client starts downloading the events
     * from the calendar.
     */
    void loadingEventsStarted();

    /**
     * @brief loadingEventsFinished is emitted after loadingEventsStarted() when the client
     * has finished loading the events.
     */
    void loadingEventsFinished();
    
};

#endif // CALENDARCLIENT_H
