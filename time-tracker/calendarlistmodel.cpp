#include "calendarlistmodel.h"
#include <QDebug>

extern "C" {
    #include <glib.h>
}

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
CalendarListModel::setCalendarList(GDataFeed *calendars)
{
    qDeleteAll(m_calendars->begin(), m_calendars->end());
    m_calendars->clear();

    // Scan the list of calendars
    GList *i;
    for (i = gdata_feed_get_entries (calendars); i != NULL; i = i->next) {
        qDebug() <<  "Calendar found: " << gdata_entry_get_title (GDATA_ENTRY (i->data));
        m_calendars->append(new Calendar (NULL, GDATA_CALENDAR_CALENDAR (i->data)));
    }

    reset();
}

GDataCalendarCalendar*
CalendarListModel::getCalendar(int index)
{
    GDataCalendarCalendar* calendar = m_calendars->at(index)->getCalendar();
    return calendar;
}
