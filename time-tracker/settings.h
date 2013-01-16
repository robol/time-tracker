#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#define TIME_TRACKER_ORGANIZATION "it.robol"
#define TIME_TRACKER_APPLICATION  "TimeTracker"

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SETTINGS_H
