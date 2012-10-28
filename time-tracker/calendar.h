#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QList>

extern "C" {
    #include <gdata/services/calendar/gdata-calendar-calendar.h>
}

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent, GDataCalendarCalendar *calendar);
    ~Calendar();

    /**
     * @brief getCalendar Return the libgdata calendar object stored inside this wrapper.
     * @return A pointer to the GDataCalendarCalendar gobject.
     */
    GDataCalendarCalendar *getCalendar();

    /**
     * @brief getTitle is the accessor method for the Title of the calendar.
     * @return The title of this calendar.
     */
    QString getTitle();

private:

    /**
     * @brief m_calendar is the private pointer to the GDataCalendarCalendar* object.
     */
    GDataCalendarCalendar *m_calendar;
    
};

#endif // CALENDAR_H
