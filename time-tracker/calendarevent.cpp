#include "calendarevent.h"

CalendarEvent::CalendarEvent(QObject *parent, GDataCalendarEvent *entry) :
    QObject(parent), m_entry (entry)
{
    m_date = NULL;
    g_object_ref (m_entry);
}

CalendarEvent::~CalendarEvent()
{
    g_object_unref (m_entry);
}

QString
CalendarEvent::getTitle()
{
    return QString (gdata_entry_get_title (GDATA_ENTRY (m_entry)));
}

QDateTime
CalendarEvent::getStart()
{
    if (!m_date)
        gdata_calendar_event_get_primary_time (m_entry, NULL, NULL, &m_date);

    if (m_date)
        return QDateTime::fromTime_t(gdata_gd_when_get_start_time (m_date));
    else
        return QDateTime();
}

QDateTime
CalendarEvent::getEnd()
{
    if (!m_date)
        gdata_calendar_event_get_primary_time (m_entry, NULL, NULL, &m_date);

    if (m_date)
        return QDateTime::fromTime_t(gdata_gd_when_get_end_time (m_date));
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
