#include "SettingsManager.h"

#include <QDebug>

SettingsManager::SettingsManager():QSettings("settings.ini",QSettings::IniFormat)
    {
    }
