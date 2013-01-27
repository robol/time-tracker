#ifndef CALENDARCLIENT_H
#define CALENDARCLIENT_H

#include <QObject>
#include "eventlistmodel.h"
#include "calendarlistmodel.h"
#include "oauth2.h"
#include "calendar_data_manager.h"

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

    /**
     * @brief performAuthentication, as the name suggests, ask the user with a login
     * dialog to perform authentication against Google servers using OAuth2.
     */
    void performAuthentication();

    /**
     * @brief clearToken can be used to remove the previous authentication.
     */
    void clearToken();

    /**
     * @brief setAuthorizationToken can be used to set the authorization token retrieved
     * opening a webpage on the URL given by loginHandlerRequired().
     * @param token is the authorization token obtained in the process above.
     */
    void setAuthorizationToken(QString token);

private:

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
     * @brief m_oauth2 is the current OAuth2 implementation.
     */
    OAuth2 m_oauth2;

    /**
     * @brief m_calendarDataManager is the object used to retrieve data about
     * user calendars.
     */
    CalendarDataManager m_calendarDataManager;

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
     * @brief m_activeCalendar is the currently selected calendar.
     */
    Calendar* m_activeCalendar;

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
    void loadingEventsStarted();

    /**
     * @brief loadingEventsFinished is emitted after loadingEventsStarted() when the client
     * has finished loading the events.
     */
    void loadingEventsFinished();

    /**
     * @brief loginHandlerRequired must be connected to a slot that will open a webpage
     * with the given url, and will wait for the user to complete the authorization process.
     * If it does end successfully it should then call setAuthorizationToken().
     */
    void loginHandlerRequired(QUrl url);

private slots:
    /**
     * @brief onLoginDone perform the necessary actions needed after a succesful
     * login. In particular, the list of calendars inside m_calendarListModel is
     * refreshed.
     */
    void onLoginDone();

    /**
     * @brief reloadCalendarList reload the list of calendars inside the m_calendarListModel.
     */
    void reloadCalendarList();

    /**
     * @brief reloadEventsList reload the list of events insde the m_eventListModel.
     */
    void reloadEventList();

    /**
     * @brief oauth2LoginHandlerRequired call the signal loginHandlerRequired with the parameter
     * obtained by the OAuth2 module.
     */
    void oauth2LoginHandlerRequired(QUrl url);
    
};

#endif // CALENDARCLIENT_H
