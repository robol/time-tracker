#include "settings.h"

Settings::Settings(QObject *parent) :
    QSettings(TIME_TRACKER_ORGANIZATION, TIME_TRACKER_APPLICATION, parent)
{
}
