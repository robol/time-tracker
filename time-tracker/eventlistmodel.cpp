#include "eventlistmodel.h"
extern "C" {
    #include <glib.h>
}

EventListModel::EventListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_events = NULL;
    reset();
}

void
EventListModel::setEventsArray(GDataFeed *array)
{
    m_events = array;
    m_length = (array) ? g_list_length (gdata_feed_get_entries (m_events)) : 0;

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
        GDataEntry *entry = (GDataEntry*) g_list_nth_data ((GList*) m_events, index.row());
        QString title = gdata_entry_get_title (entry);
        g_object_unref (entry);
        return title;
    }
    else
        return QVariant();
}

CalendarEvent*
EventListModel::getEventAt(int position)
{
    GDataCalendarEvent *entry = (GDataCalendarEvent*) g_list_nth_data ((GList*) m_events, position);
    g_object_unref (entry);
    return new CalendarEvent(this, entry);
}
