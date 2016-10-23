#include "SettingsManager.h"

SettingsManager::SettingsManager():QSettings("settings.ini",QSettings::IniFormat)
	{
	}
