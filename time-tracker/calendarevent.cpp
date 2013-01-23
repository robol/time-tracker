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
    if (!m_eventData.contains("summary")) {
        return QString("");
    }

    return m_eventData["summary"].toString();
}

QDateTime
CalendarEvent::getStart(QTime dayStart)
{
    QMap<QString,QVariant> start = m_eventData["start"].toMap();
    if (start.contains("dateTime"))
        return start["dateTime"].toDateTime();
    else
        return start["date"].toDateTime().addSecs(((dayStart.hour() * 60) + dayStart.minute() * 60) + dayStart.second());
}

QDateTime
CalendarEvent::getEnd(QTime dayEnd)
{
    QMap<QString,QVariant> end = m_eventData["end"].toMap();
    if (end.contains("dateTime"))
         return end["dateTime"].toDateTime();
    else
        return end["date"].toDateTime().addSecs(((dayEnd.hour() * 60) + dayEnd.minute() * 60) + dayEnd.second());
}

double
CalendarEvent::getDuration(QTime dayStart, QTime dayEnd)
{
    QDateTime start = getStart(dayStart);
    QDateTime end = getEnd(dayEnd);

    if (start.isNull() || end.isNull())
        return 0;
    else
    {
        // We need the cast to double to be sure that no rounding
        // is made in integer arithmetic.
        return ((double) start.secsTo(end)) / 3600.0;
    }
}
