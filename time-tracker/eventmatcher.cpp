#include "eventmatcher.h"

EventMatcher::EventMatcher(QString matchString) :
    m_matchString(matchString.toLower())
{
}

bool
EventMatcher::match(CalendarEvent& event)
{
    QString title = event.getTitle();
    return title.toLower().contains(m_matchString);
}
