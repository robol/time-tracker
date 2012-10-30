#include "calendar.h"

Calendar::Calendar(QObject *parent) :
    QObject(parent)
{
}

Calendar::~Calendar()
{
}

//GDataCalendarCalendar*
//Calendar::getCalendar()
//{
//    return m_calendar;
//}

QString
Calendar::getTitle()
{
    return "";
}
