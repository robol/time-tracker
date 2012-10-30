#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QVariant>

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent, QMap<QString, QVariant> calendar_data);
    ~Calendar();

    /**
     * @brief getTitle is the accessor method for the Title of the calendar.
     * @return The title of this calendar.
     */
    QString getTitle();

    /**
     * @brief getId can be used to access the identifier of the calendar
     * inside Google Calendar.
     * @return A string with the requested id.
     */
    QString getId();

private:
    QMap<QString, QVariant> m_calendarData;
    
};

#endif // CALENDAR_H
