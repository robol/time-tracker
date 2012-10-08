#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QObject>
#include <QDateTime>
extern "C" {
    #include <gcalendar.h>
}

/**
 * @brief The CalendarEvent class is wrapper around gcal_event_t objects.
 * Its main purpose is to give handy accessors to the Event data using Qt types.
 */
class CalendarEvent : public QObject
{
    Q_OBJECT
public:
    explicit CalendarEvent(QObject *parent = 0, gcal_event_t event = NULL);

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


private:
    gcal_event_t m_event;
    
signals:
    
public slots:
    
};

#endif // CALENDAREVENT_H
