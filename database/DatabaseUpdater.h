#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H

#include <QObject>
#include "DbFileItem.h"
#include <QWidget>
#include "../gui/selectDb/DatabaseUpdateWindow.h"
#include <QThread>

class DbFileItem;

class DatabaseUpdater : public QObject
	{
		Q_OBJECT
	public:
		explicit DatabaseUpdater(QObject *parent = 0);
                void update(DbFileItem & file);
        signals:
                void setMaxValue(int max);
                void setValue(int value);
                void finished();
                void error(QString);
	};

#endif // DATABASEUPDATER_H
