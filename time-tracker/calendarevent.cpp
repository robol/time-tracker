#include "calendarevent.h"

CalendarEvent::CalendarEvent(QObject *parent) :
    QObject(parent)
{

}

CalendarEvent::~CalendarEvent()
{
}

QString
CalendarEvent::getTitle()
{
    return "";
}

QDateTime
CalendarEvent::getStart()
{
    return QDateTime();
}

QDateTime
CalendarEvent::getEnd()
{
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
