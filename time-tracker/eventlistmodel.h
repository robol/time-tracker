#ifndef EVENTLISTMODEL_H
#define EVENTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "calendarevent.h"

extern "C" {
    #include <gdata/services/calendar/gdata-calendar-event.h>
    #include <gdata/gdata-feed.h>
}

class EventListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EventListModel(QObject *parent = 0);
    void setEventsArray(GDataFeed *events);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief getEventAt returns the Event stored in the specified
     * position.
     * @param position Is the index where the event is found.
     * @return A pointer to an
     */
    CalendarEvent* getEventAt(int position);

private:
    QList<CalendarEvent*> * m_events;
    int m_length;
    
};

#endif // EVENTLISTMODEL_H
