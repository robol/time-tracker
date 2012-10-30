#ifndef EVENTLISTMODEL_H
#define EVENTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "calendarevent.h"

class EventListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EventListModel(QObject *parent = 0);

    /**
     * @brief addEvents Add events to the model. Can be called while retrieving
     *                  these from Google Calendar.
     * @param events The GDataFeed points obtained by a call to
     *               gdata_calendar_service_query_events().
     */
    void addEvents();

    /**
     * @brief rowCount counts the total number of elements in the Model.
     * @param parent Is bogus. Will not be used.
     * @return The number of elements in the model.
     */
    int rowCount(const QModelIndex &parent) const;

    /**
     * @brief data returns the display data for the Model.
     * @param index Is the QModelIndex pointing to the position that has to
     *        be displayed.
     * @param role Is the requested role for the data
     * @return The data to be displayed, or the indication for doing so.
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief getEventAt returns the Event stored in the specified
     * position.
     * @param position Is the index where the event is found.
     * @return A pointer to an
     */
    CalendarEvent* getEventAt(int position);

    /**
     * @brief clearEvents purges the List of events present in the model,
     * freeing the associated CalendarEvents objects.
     */
    void clearEvents();

private:
    QList<CalendarEvent*> * m_events;
    
};

#endif // EVENTLISTMODEL_H
