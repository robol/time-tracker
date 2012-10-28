#include "calendarlistmodel.h"

extern "C" {
    #include <glib.h>
}

CalendarListModel::CalendarListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_calendars = NULL;
}

CalendarListModel::~CalendarListModel()
{
    if (m_calendars)
        g_object_unref (m_calendars);
}

int
CalendarListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (!m_calendars)
        return 0;

    GValue total_results;
    g_object_get_property (G_OBJECT (m_calendars), "total-results", &total_results);
    return g_value_get_int (&total_results);
}

QVariant
CalendarListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        GList * entries = gdata_feed_get_entries (m_calendars);
        GDataEntry *entry = GDATA_ENTRY (g_list_nth_data (entries, index.row()));
        QString displayText = gdata_entry_get_title (entry);
        g_object_unref (entry);
        g_object_unref (entries);
        return displayText;
    }
    else
        return QVariant();
}

void
CalendarListModel::setCalendarList(GDataFeed *calendars)
{
    m_calendars = calendars;
    g_object_ref (m_calendars);
    reset();
}

GDataCalendarCalendar*
CalendarListModel::getCalendar(int index)
{
    GList *entries = gdata_feed_get_entries (m_calendars);
    GDataCalendarCalendar* calendar = GDATA_CALENDAR_CALENDAR (g_list_nth_data (entries, index));
    g_object_unref (entries);
    return calendar;
}
