#include "calendarlistmodel.h"

extern "C" {
    #include "glib.h"
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

    return m_calendars->length;
}

QVariant
CalendarListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        gcal_t calendar;
        gcal_get_calendar_by_index(m_calendars, index.row(), &calendar);
        return QString (gcal_resource_get_user(calendar));
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
    GDataCalendarCalendar* calendar = (GCalendarCalendar*) g_list_get_nth_data (entries, index);
    g_object_unref (entries);
    return calendar;
}
