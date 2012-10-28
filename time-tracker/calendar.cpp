#include "calendar.h"

Calendar::Calendar(QObject *parent, GDataCalendarCalendar *calendar) :
    QObject(parent), m_calendar (calendar)
{
    g_object_ref (calendar);
}

Calendar::~Calendar()
{
    g_object_unref (m_calendar);
}

GDataCalendarCalendar*
Calendar::getCalendar()
{
    return m_calendar;
}

QString
Calendar::getTitle()
{
    return QString(gdata_entry_get_title (GDATA_ENTRY (m_calendar)));
}
