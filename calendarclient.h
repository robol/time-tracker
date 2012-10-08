#ifndef CALENDARCLIENT_H
#define CALENDARCLIENT_H

#include <QObject>

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

private:

    void performAuthentication();

    QString m_username;
    QString m_password;

    gcal_t m_client;
    
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
    
public slots:
    
};

#endif // CALENDARCLIENT_H
