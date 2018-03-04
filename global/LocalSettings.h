#ifndef LOCALSETTINGS_H
#define LOCALSETTINGS_H

#include <QSettings>
#include "../database/ExternalAppItem.h"
#include <QList>

bool exAppLessThan(const ExternalAppItem* i1,const ExternalAppItem* i2);

class LocalSettings : public QSettings
	{
		Q_OBJECT
	public:
		LocalSettings();
		QList<ExternalAppItem*> getExternalAppList();
		void setExternalAppList(QList<ExternalAppItem*> list);

	};

#endif // LOCALSETTINGS_H
