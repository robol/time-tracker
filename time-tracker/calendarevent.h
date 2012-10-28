#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QObject>
#include <QDateTime>
extern "C" {
    #include <gdata/services/calendar/gdata-calendar-event.h>
    #include <gdata/gd/gdata-gd-when.h>
}

/**
 * @brief The CalendarEvent class is wrapper around gcal_event_t objects.
 * Its main purpose is to give handy accessors to the Event data using Qt types.
 */
class CalendarEvent : public QObject
{
    Q_OBJECT
public:
    explicit CalendarEvent(QObject *parent = 0, GDataCalendarEvent *event = NULL);
    ~CalendarEvent();

    /**
     * @brief getTitle is the accessor for the title property of the event
     * @return the title of the event.
     */
    QString getTitle();

    /**
     * @brief getStart returns the start of the event, if set, or an invalid
     * QDateTime object otherwise.
     * @return The start of the event.
     */
    QDateTime getStart();

    /**
     * @brief getEnd returns the end of the event, if set, or an invalid
     * QDateTime object otherwise.
     * @return The end of the event.
     */
    QDateTime getEnd();

    /**
     * @brief getDuration can be used to find the duration of an event. In the case
     * of an event without a start and/or end date, 0 is returned.
     *
     * @return The duration of the even in hours, or 0.0 if no start and/or end
     * date are set.
     */
    double getDuration();


private:
    GDataCalendarEvent *m_entry;
    GDataGDWhen *m_date;
    
signals:
    
public slots:
    
};

#endif // CALENDAREVENT_H
