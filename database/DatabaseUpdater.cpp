#include "DatabaseUpdater.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>

DatabaseUpdater::DatabaseUpdater(QObject *parent) : QObject(parent)
	{
	}



void DatabaseUpdater::update(DbFileItem& file)
	{
	QStringList script = file.prepareUpdateScript();
	emit this->setMaxValue(script.count());
	emit this->setValue(0);


	{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","dbUpdate");
	db.setDatabaseName(file.fileName);

	if(db.open())
		{
		QSqlQuery q(db);
		bool error =false;
		db.transaction();
		for(int i=0;i<script.count() && !error ;i++)
			{
			if(!script.at(i).trimmed().isEmpty())
				{
				q.prepare(script.at(i));
				if(!q.exec())
					{
					error=true;
					qDebug()<<db.lastError().text();
					emit this->error(db.lastError().text());
					}
				}
			emit this->setValue(i+1);
			}

		if(error)
			{
			db.rollback();
			}
		else
			{
			db.commit();
			}
		db.close();
		}
	}

	QSqlDatabase::removeDatabase("dbUpdate");


	emit this->finished();
	}
