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

    GDataCalendarCalendar *getCalendar();
    QString getTitle();

private:
    GDataCalendarCalendar *m_calendar;
    
};

#endif // CALENDAR_H
