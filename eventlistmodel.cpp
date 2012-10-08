#include "eventlistmodel.h"

EventListModel::EventListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_isEmpty = true;
    reset();
}

void
EventListModel::setEventsArray(gcal_event_array* array)
{
    m_events = array;

    // Fill the data in the model to respect
    m_isEmpty = m_events->length == 0;
    reset();
}

int
EventListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (m_isEmpty)
        return 0;
    else
        return m_events->length;
}

QVariant
EventListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return gcal_event_get_title(gcal_event_element(m_events, index.row()));
    }
    else
        return QVariant();
}

gcal_event_t
EventListModel::getEventAt(int position)
{
    return gcal_event_element(m_events, position);
}
