#include "calendarlistmodel.h"
#include <QDebug>

CalendarListModel::CalendarListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_calendars = new QList<Calendar*>();
}

CalendarListModel::~CalendarListModel()
{
    delete m_calendars;
}

int
CalendarListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_calendars->length();
}

QVariant
CalendarListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_calendars->at(index.row())->getTitle();
    }
    else
        return QVariant();
}

void
CalendarListModel::setCalendarList()
{
    qDeleteAll(m_calendars->begin(), m_calendars->end());
    m_calendars->clear();

    reset();
}

//GDataCalendarCalendar*
//CalendarListModel::getCalendar(int index)
//{
//    GDataCalendarCalendar* calendar = m_calendars->at(index)->getCalendar();
//    return calendar;
//}
