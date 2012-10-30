#include "calendar.h"

Calendar::Calendar(QObject *parent, QMap<QString, QVariant> calendarData) :
    QObject(parent), m_calendarData(calendarData)
{
}

Calendar::~Calendar()
{
}

QString
Calendar::getId()
{
    return m_calendarData["id"].toString();
}

QString
Calendar::getTitle()
{
    return m_calendarData["summary"].toString();
}
