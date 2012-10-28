#include "eventlistmodel.h"
extern "C" {
    #include <glib.h>
}

EventListModel::EventListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_events = new QList<CalendarEvent*>();
}

void
EventListModel::setEventsArray(GDataFeed *array)
{
    qDeleteAll(m_events->begin(), m_events->end());
    m_events->clear();

    GList *i;
    for (i = gdata_feed_get_entries (array); i != NULL; i = i->next) {
        m_events->append(new CalendarEvent (NULL, GDATA_CALENDAR_EVENT (i->data)));
    }

    m_length = m_events->length();

    // Fill the data in the model to respect
    reset();
}

int
EventListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_length;
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
