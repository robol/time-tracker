#ifndef EVENTLISTMODEL_H
#define EVENTLISTMODEL_H

#include <QAbstractListModel>
#include "calendarevent.h"

extern "C" {
    #include <gcalendar.h>
}

class EventListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EventListModel(QObject *parent = 0);
    void setEventsArray(gcal_event_array* array);
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
    bool m_isEmpty;
    gcal_event_array *m_events;

signals:
    
public slots:
    
};

#endif // EVENTLISTMODEL_H
