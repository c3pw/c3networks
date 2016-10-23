#ifndef LOCALSETTINGS_H
#define LOCALSETTINGS_H

#include <QSettings>

class LocalSettings : public QSettings
	{
		Q_OBJECT
	public:
		LocalSettings();
	};

#endif // LOCALSETTINGS_H
