#ifndef CALENDARLISTMODEL_H
#define CALENDARLISTMODEL_H

#include <QAbstractListModel>
#include "calendar.h"

extern "C" {
    #include <gdata/services/calendar/gdata-calendar-calendar.h>
    #include <gdata/services/calendar/gdata-calendar-feed.h>
}

/**
 * @brief The CalendarListModel class is a wrapper around the list of calendars
 * that a user have in Google Calendar.
 */
class CalendarListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CalendarListModel(QObject *parent = 0);
    ~CalendarListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief setCalendarList can be used to set the current list of calendars available.
     * @param calendars The array structure obtained by a call to gcal_calendar_list().
     */
    void setCalendarList(GDataFeed *calendars);

    /**
     * @brief getCalendar returns the gcal_t object associated with a given QModelIndex
     * @param index the Index in the Model where the calendar is placed.
     * @return The gcal_t object, i.e., the opaque pointer to the gcal_resource structure.
     */
    GDataCalendarCalendar* getCalendar(int index);

private:
    QList<Calendar*> *m_calendars;
    
};

#endif // CALENDARLISTMODEL_H
