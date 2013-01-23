#ifndef EVENTMATCHER_H
#define EVENTMATCHER_H

#include <QString>
#include "calendarevent.h"

class EventMatcher
{
public:
    EventMatcher(QString matchString);

    /**
     * @brief Test if the given test string matches
     * the matchString specified when this object was
     * instantiated.
     *
     * @return TRUE if test matches matchString, FALSE otherwise.
     */
    bool match(CalendarEvent& event);

private:
    QString m_matchString;
};

#endif // EVENTMATCHER_H
