#include "calendarclient.h"
#include <QDebug>
#include <QtConcurrentRun>

CalendarClient::CalendarClient(QObject *parent) :
    QObject(parent)
{
    m_client = gcal_new(GCALENDAR);
}

void
CalendarClient::performAuthentication()
{
    // Get a Byte representation of username and password, since we need
    // const char * to be passed to the libgcal methods.
    QByteArray username_data = m_username.toLatin1();
    QByteArray password_data = m_password.toLatin1();

    // Try to authenticate on Google Calendar, and give a warning if it does
    // not succeed.
    int result = gcal_get_authentication(m_client, username_data.data(), password_data.data());
    if (result != 0)
    {
        qDebug() << "Warning: Authentication failed on Google Calendar";
        authenticationFailed();
    }
    else
        connected();
}

void
CalendarClient::setAuthenticationData(QString username, QString password)
{
    m_username = username;
    m_password = password;

    QtConcurrent::run(this, &CalendarClient::performAuthentication);
}
