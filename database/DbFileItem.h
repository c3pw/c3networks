#ifndef DBFILEITEM_H
#define DBFILEITEM_H

#include <QObject>
#include <QSqlDatabase>
#include "DatabaseUpdater.h"

class DatabaseUpdater;

class DbFileItem : public QObject
	{
		Q_OBJECT
	public:
		DbFileItem(QObject *parent = 0);
		DbFileItem(const DbFileItem &source, QObject *parent = 0);
		void operator =(const DbFileItem &source);

		static const int version = 5;

		QString getFileName() const;
		void setFileName(const QString &value);
		QString getDescription() const;
		void setDescription(const QString &value);
		QString getName() const;
		void setName(const QString &value);

		bool fileExists();
		int getDatabaseVersion();
		bool isUpdateRequired();

	private:
		QString fileName;
		QString description;
		QString name;
		QStringList prepareUpdateScript();

		friend DatabaseUpdater;
	};

#endif // DBFILEITEM_H
