#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QList>

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent);
    ~Calendar();

    /**
     * @brief getCalendar Return the libgdata calendar object stored inside this wrapper.
     * @return A pointer to the GDataCalendarCalendar gobject.
     */
    // GDataCalendarCalendar *getCalendar();

    /**
     * @brief getTitle is the accessor method for the Title of the calendar.
     * @return The title of this calendar.
     */
    QString getTitle();

private:
    
};

#endif // CALENDAR_H
