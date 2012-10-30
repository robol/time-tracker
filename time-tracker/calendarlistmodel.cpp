#include "calendarlistmodel.h"
#include <QDebug>

CalendarListModel::CalendarListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

CalendarListModel::~CalendarListModel()
{
}

int
CalendarListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_calendars.length();
}

QVariant
CalendarListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_calendars.at(index.row())->getTitle();
    }
    else
        return QVariant();
}

void
CalendarListModel::setCalendarList(QList<Calendar*> calendars)
{
    // Remove calendars that were already in the list, if any.
    qDeleteAll(m_calendars.begin(), m_calendars.end());
    m_calendars.clear();

    m_calendars = calendars;

    reset();
}

Calendar*
CalendarListModel::getCalendar(int index)
{
    return m_calendars.at(index);
}
