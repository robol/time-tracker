#include "calendarlistmodel.h"

CalendarListModel::CalendarListModel(QObject *parent) :
    QAbstractListModel(parent), isEmpty(true)
{
}

CalendarListModel::~CalendarListModel()
{
    delete m_calendars;
}

int
CalendarListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (isEmpty)
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
CalendarListModel::setCalendarList(gcal_resource_array *calendars)
{
    m_calendars = calendars;
    isEmpty = calendars->length == 0;

    reset();
}

gcal_t
CalendarListModel::getCalendar(int index)
{
    gcal_t calendar;
    gcal_get_calendar_by_index(m_calendars, index, &calendar);
    return calendar;
}
