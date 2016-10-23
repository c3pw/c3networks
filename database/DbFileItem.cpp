#include "DbFileItem.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QSqlError>


#include <QDebug>
DbFileItem::DbFileItem(QObject *parent) : QObject(parent)
	{

	}

DbFileItem::DbFileItem(const DbFileItem &source,QObject *parent) : QObject(parent)
	{
	this->fileName = source.fileName;
	this->name = source.name;
	this->description = source.description;
	}

void DbFileItem::operator =(const DbFileItem &source)
	{
	this->fileName = source.fileName;
	this->name = source.name;
	this->description = source.description;
	}

QString DbFileItem::getFileName() const
	{
	return fileName;
	}

void DbFileItem::setFileName(const QString &value)
	{
	fileName = value;
	}

QString DbFileItem::getDescription() const
	{
	return description;
	}

void DbFileItem::setDescription(const QString &value)
	{
	description = value;
	}

QString DbFileItem::getName() const
	{
	return name;
	}

void DbFileItem::setName(const QString &value)
	{
	name = value;
	}

bool DbFileItem::fileExists()
	{
	return QFile(this->fileName).exists();
	}

int DbFileItem::getDatabaseVersion()
	{
	if(!this->fileExists()){return 0;}
	int version = 0;

	{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","vCheck");
	db.setDatabaseName(this->fileName);
	if(db.open())
		{
		QSqlQuery q(db);
		q.prepare("select max(version) from versions;");
		if(q.exec())
			{
			q.first();
			QVariant v =  q.value(0);
			if(v.isValid())
				{
				version = v.toInt();
				}
			}
		}
	db.close();
	}

	QSqlDatabase::removeDatabase("vCheck");
	return version;
	}

bool DbFileItem::isUpdateRequired()
	{
	int v = this->getDatabaseVersion();
	return (v>0 && v<this->version);
	}

QStringList DbFileItem::prepareUpdateScript()
	{
	QStringList script;
	int v = this->getDatabaseVersion();
	QString scriptName="";
	QFile f;
	QString tym="";
	for(int i=v;i<this->version;i++)
		{
		scriptName = ":/db/u"+QString::number(i)+"to"+QString::number(i+1)+".sql";
		f.setFileName(scriptName);
		if(f.exists())
			{
			if(f.open(QIODevice::ReadOnly))
				{
				tym = f.readAll();
				script.append(tym.split(";"));
				f.close();
				}
			}
		}
	return script;
	}

/*bool DbFileItem::openDbConnection()
	{
	QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(this->getFileName());
	return db.open();
	}

bool DbFileItem::analizeFile(QWidget *parent)
	{
	QFileInfo fi(this->fileName);
	if(!fi.isFile())
		{
		QMessageBox m(parent);
		m.setWindowTitle(tr("Error"));
		m.setIcon(QMessageBox::Critical);
		m.setText(tr("File not found."));
		m.exec();
		return false;
		}
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","vCheck");
	db.setDatabaseName(this->fileName);
	if(db.open())
		{
		QSqlQuery q(db);
		q.prepare("select max(version) from versions;");
		if(!q.exec())
			{
			QMessageBox m(parent);
			m.setWindowTitle(tr("Error"));
			m.setIcon(QMessageBox::Critical);
			m.setText(tr("File corrupted."));
			m.exec();
			q.clear();
			db.close();
			QSqlDatabase::removeDatabase("vCheck");
			return false;
			}
		q.next();
		QVariant v = q.value(0);
		if(v.isValid())
			{
			int version = v.toInt();
			if(version > this->version)
				{
				QMessageBox m(parent);
				m.setWindowTitle(tr("Error"));
				m.setIcon(QMessageBox::Critical);
				QString message = tr("File cannot be open.\nFile version: #");
				message.append(QString::number(version));
				message.append("\n");
				message.append(tr("Required: #"));
				message.append(QString::number(this->version));
				m.setText(message);
				m.exec();
				q.clear();
				db.close();
				QSqlDatabase::removeDatabase("vCheck");
				return false;
				}
			if(version<this->version)
				{
				QMessageBox m;
				m.setWindowTitle(tr("Question"));
				m.setIcon(QMessageBox::Question);
				m.setText("Database is in an old version. Would You like to update?");
				m.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
				m.setDefaultButton(QMessageBox::Yes);
				if(m.exec()==QMessageBox::Yes)
					{
					db.transaction();
					bool ret = update(db,version);
					if(ret)
						{
						db.commit();
						}
					else
						{
						db.rollback();
						}
					db.close();

					q.clear();
					QSqlDatabase::removeDatabase("vCheck");
					return ret;
					}
				db.close();

				q.clear();
				QSqlDatabase::removeDatabase("vCheck");
				return false;
				}
			}

		q.clear();
		db.close();
		QSqlDatabase::removeDatabase("vCheck");
		}
	return true;
	}

bool DbFileItem::update(QSqlDatabase db, int version)
	{
	QString script;
	for(int i= version; i < this->version;i++)
		{
		script=":/db/u"+QString::number(i)+"to"+QString::number(i+1)+".sql";
		if(!executeScript(db,script))
			{
			return false;
			}
		}
	return true;
	}

bool DbFileItem::executeScript(QSqlDatabase db, QString scriptFile)
	{
	QFile f(scriptFile);
	if(!f.open(QIODevice::ReadOnly))
		{
		return false;
		}
	QStringList commands = QString(f.readAll()).split(";");
	f.close();

	QSqlQuery q(db);
	for(int i=0; i< commands.count();i++)
		{
		QString c = commands.at(i).trimmed();
		if(!c.isEmpty())
			{
			q.prepare(c+";");
			if(!q.exec())
				{
				return false;
				}
			}
		}
	q.clear();
	return true;
	}
*/








