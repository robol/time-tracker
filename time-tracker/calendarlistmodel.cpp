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
    QList<Calendar*> oldList = m_calendars;
    m_calendars = calendars;

    // Remove calendars that were already in the list, if any.
    qDeleteAll(oldList.begin(), oldList.end());
    oldList.clear();

    reset();
}

Calendar*
CalendarListModel::getCalendar(int index)
{
    return m_calendars.at(index);
}
