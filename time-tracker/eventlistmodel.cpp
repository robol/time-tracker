#include "eventlistmodel.h"

EventListModel::EventListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_events = new QList<CalendarEvent*>();
}

void
EventListModel::clearEvents()
{
    qDeleteAll(m_events->begin(), m_events->end());
    m_events->clear();
}

void
EventListModel::addEvents()
{
    // Fill the data in the model to respect
    reset();
}

int
EventListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_events->length ();
}

QVariant
EventListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_events->at(index.row())->getTitle();
    }
    else
        return QVariant();
}

CalendarEvent*
EventListModel::getEventAt(int position)
{
    return m_events->at(position);
}
