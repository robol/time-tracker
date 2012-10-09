#include "calendarevent.h"

CalendarEvent::CalendarEvent(QObject *parent, gcal_event_t event) :
    QObject(parent), m_event (event)
{
}

QString
CalendarEvent::getTitle()
{
    return QString (gcal_event_get_title(m_event));
}

QDateTime
CalendarEvent::getStart()
{
    const char * date_iso = gcal_event_get_start(m_event);
    if (date_iso)
        return QDateTime::fromString(QString(date_iso), Qt::ISODate);
    else
        return QDateTime();
}

QDateTime
CalendarEvent::getEnd()
{
    const char * date_iso = gcal_event_get_end(m_event);
    if (date_iso)
        return QDateTime::fromString(QString(date_iso), Qt::ISODate);
    else
        return QDateTime();
}

double
CalendarEvent::getDuration()
{
    QDateTime start = getStart();
    QDateTime end = getEnd();

    if (start.isNull() || end.isNull())
        return 0;
    else
    {
        // We need the cast to double to be sure that no rounding
        // is made in integer arithmetic.
        return ((double) start.secsTo(end)) / 3600.0;
    }
}
