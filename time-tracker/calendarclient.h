#ifndef CALENDARCLIENT_H
#define CALENDARCLIENT_H

#include <QObject>
#include "eventlistmodel.h"
#include "calendarlistmodel.h"

extern "C" {
    #include <gcalendar.h>
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

    void performAuthentication();

    QString m_username;
    QString m_password;

    gcal_t m_client;
    gcal_event_array m_events;

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
    
signals:
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
    void loadingEventStarted();

    /**
     * @brief loadingEventsFinished is emitted after loadingEventsStarted() when the client
     * has finished loading the events.
     */
    void loadingEventsFinished();
    
public slots:
    
};

#endif // CALENDARCLIENT_H
