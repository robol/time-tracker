#ifndef EVENTLISTMODEL_H
#define EVENTLISTMODEL_H

#include <QAbstractListModel>

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

    gcal_event_t getEventAt(int position);

private:
    bool m_isEmpty;
    gcal_event_array *m_events;

signals:
    
public slots:
    
};

#endif // EVENTLISTMODEL_H
