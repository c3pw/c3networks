#include "LocalSettings.h"
#include <QColor>

LocalSettings::LocalSettings():QSettings(QSettings::IniFormat,QSettings::UserScope,"pworwag.com.pl","c3networks")
	{
	if(!allKeys().contains("rememberFilterMode"))
		{
		setValue("rememberFilterMode",true);
		}
	if(!allKeys().contains("filterHilightColor"))
		{
		setValue("filterHilightColor",QColor(0, 255, 0, 50));
		}
	if(!allKeys().contains("cp852conversion"))
		{
		setValue("cp852conversion",true);
		}
	}
