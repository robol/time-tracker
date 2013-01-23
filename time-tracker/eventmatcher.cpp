#include "eventmatcher.h"

EventMatcher::EventMatcher(QString matchString) :
    m_matchString(matchString.toLower())
{
}

bool
EventMatcher::match(CalendarEvent& event)
{
    QString title = event.getTitle();

    // If Dates are valid, check them
    if (m_StartDate.isValid() && m_StartDate >= event.getStart()) {
        return false;
    }

    if (m_EndDate.isValid() && m_EndDate <= event.getEnd()) {
        return false;
    }

    return title.toLower().contains(m_matchString);
}

void
EventMatcher::setStartDate(QDateTime start)
{
    m_StartDate = start;
}

void
EventMatcher::setEndDate(QDateTime end)
{
    m_EndDate = end;
}
