#include "calendarevent.h"
#include <QDebug>

CalendarEvent::CalendarEvent(QObject *parent, QMap<QString, QVariant> eventData) :
    QObject(parent), m_eventData(eventData)
{
}

CalendarEvent::~CalendarEvent()
{
}

QString
CalendarEvent::getTitle()
{
    return m_eventData["summary"].toString();
}

QDateTime
CalendarEvent::getStart()
{
    QMap<QString,QVariant> start = m_eventData["start"].toMap();
    if (start.contains("dateTime"))
        return start["dateTime"].toDateTime();
    else
        return start["date"].toDateTime().addSecs(3600 * 8);
}

QDateTime
CalendarEvent::getEnd()
{
    QMap<QString,QVariant> end = m_eventData["end"].toMap();
    if (end.contains("dateTime"))
         return end["dateTime"].toDateTime();
    else
         return end["date"].toDateTime().addSecs(3600 * 19);
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
