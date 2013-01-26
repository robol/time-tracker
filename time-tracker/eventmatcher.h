#ifndef EVENTMATCHER_H
#define EVENTMATCHER_H

#include <QString>
#include <QDateTime>
#include "calendarevent.h"

class EventMatcher
{
public:
    EventMatcher(QString matchString);

    /**
     * @brief Select a starting threshdold. Events before
     * this date will not match.
     */
    void setStartDate(QDateTime start);
    void setStartDate(QDate start) { setStartDate(QDateTime(start)); }

    /**
     * @brief Select and end threshold. Events after this
     * date will not match.
     */
    void setEndDate(QDateTime end);
    void setEndDate(QDate end) { setEndDate(QDateTime(end)); }

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

    QDateTime m_StartDate;
    QDateTime m_EndDate;
};

#endif // EVENTMATCHER_H
