#ifndef CALENDARLISTMODEL_H
#define CALENDARLISTMODEL_H

#include <QAbstractListModel>
#include "calendar.h"

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

    /**
     * @brief rowCount counts the number of elements in the model.
     * @param parent Is bogus, will not be used.
     * @return the number of elements present in the model.
     */
    int rowCount(const QModelIndex &parent) const;

    /**
     * @brief data Is the overriden data function for the model.
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief setCalendarList can be used to set the current list of calendars available.
     * @param calendars The array structure obtained by a call to gcal_calendar_list().
     */
    void setCalendarList();

    /**
     * @brief getCalendar returns the gcal_t object associated with a given QModelIndex
     * @param index the Index in the Model where the calendar is placed.
     * @return The gcal_t object, i.e., the opaque pointer to the gcal_resource structure.
     */
//    GDataCalendarCalendar* getCalendar(int index);

private:
    QList<Calendar*> *m_calendars;
    
};

#endif // CALENDARLISTMODEL_H
