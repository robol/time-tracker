#include "eventlistmodel.h"

EventListModel::EventListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

void
EventListModel::clearEvents()
{
    qDeleteAll(m_events.begin(), m_events.end());
    m_events.clear();
}

void
EventListModel::setEventList(QList<CalendarEvent *> events)
{
    m_events = events;
    reset();
}

int
EventListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_events.length ();
}

QVariant
EventListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_events.at(index.row())->getTitle();
    }
    else
        return QVariant();
}

CalendarEvent*
EventListModel::getEventAt(int position)
{
    return m_events.at(position);
}
