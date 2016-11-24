#include "IfDbTable.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVariant>
#include <QHostAddress>
#include <QFile>
#include <QTextStream>

IfDbTable::IfDbTable(QObject *parent) : QObject(parent)
	{
	}

void IfDbTable::addInterface(quint32 ipAddress, quint32 mask, QString name, QString mac, QString userName,
							 QString domain, QString description, bool inUse, int groupId, QString location,
							 bool dhcpReservation, int interfaceId, QString switchPort)
	{
	QSqlQuery query;

	query.prepare("insert into hosts(ipAddress,mask,name,mac,userName,domain,description,"
				  "inUse,groupId,location,dhcpReservation,interfaceId,switchPort) "
				  "values(:ipAddress,:mask,:name,:mac,:userName,:domain,:description,"
				  ":inUse,:groupId,:location,:dhcpReservation,:interfaceId,:switchPort);");


	query.bindValue(":ipAddress",ipAddress);
	query.bindValue(":mask",mask);
	query.bindValue(":name",name);
	query.bindValue(":mac",mac);
	query.bindValue(":userName",userName);
	query.bindValue(":domain",domain);
	query.bindValue(":description",description);
	query.bindValue(":inUse",inUse);
	query.bindValue(":location",location);
	query.bindValue(":dhcpReservation",dhcpReservation);
	query.bindValue(":groupId",groupId);
	query.bindValue(":interfaceId",interfaceId);
	query.bindValue(":switchPort",switchPort);

	if(groupId==0) { query.bindValue(":groupId",QVariant()); }
	if(interfaceId==0) { query.bindValue(":interfaceId",QVariant()); }


	if(query.exec())
		{
		emit prepareToModelReset();
		}
	else
		{
		qDebug()<<query.lastError().text();
		qDebug()<<query.lastQuery();
		qDebug()<<query.boundValues();
		}
	}

void IfDbTable::addInterfaces(quint32 from, quint32 to, quint32 mask, int groupId)
	{
	if(to<from){return;}

	QSqlQuery query;
	query.prepare("insert into hosts(ipAddress,mask,groupId) values(:ipAddress,:mask,:groupId);");

	QSqlDatabase::database().transaction();

	for(quint32 i=from;i<to;i++)
		{
		query.bindValue(":ipAddress",i);
		query.bindValue(":mask",mask);
		if(groupId==0)
			{
			query.bindValue(":groupId",QVariant());
			}
		else
			{
			query.bindValue(":groupId",groupId);
			}
		if(!query.exec())
			{
			QSqlDatabase::database().rollback();
			emit dbError(query.lastError().number(),query.lastError().text());
			return;
			}
		}
	QSqlDatabase::database().commit();
	emit prepareToModelReset();
	}

void IfDbTable::updateInterface(int id, quint32 ipAddress, quint32 mask, QString name, QString mac,
								QString userName, QString domain, QString description, bool inUse,
								int groupId, QString location, bool dhcpReservation,int interfaceId,QString switchPort)
	{
	QSqlQuery query;
	query.prepare("update hosts set ipAddress=:ipAddress, mask=:mask, name=:name, mac=:mac,"
				  "userName=:userName, domain=:domain,description=:description,inUse=:inUse, groupId=:groupId, location=:location"
				  ",dhcpReservation=:dhcpReservation,interfaceId=:interfaceId,switchPort=:switchPort where id=:id");
	query.bindValue(":ipAddress",ipAddress);
	query.bindValue(":mask",mask);
	query.bindValue(":name",name);
	query.bindValue(":mac",mac);
	query.bindValue(":userName",userName);
	query.bindValue(":domain",domain);
	query.bindValue(":description",description);
	query.bindValue(":inUse",inUse);
	query.bindValue(":location",location);
	query.bindValue(":dhcpReservation",dhcpReservation);
	query.bindValue(":id",id);
	query.bindValue(":groupId",groupId);
	query.bindValue(":interfaceId",interfaceId);
	query.bindValue(":switchPort",switchPort);

	if(groupId==0) { query.bindValue(":groupId",QVariant()); }

	if(interfaceId==0) { query.bindValue(":interfaceId",QVariant()); }


	if(query.exec())
		{
		emit prepareToModelReset();
		}
	}

void IfDbTable::deleteInterfaces(QList<int> idx)
	{
	if(idx.count()==0){return;}
	QSqlQuery query;
	query.prepare("delete from hosts where id=:id;");
	QSqlDatabase::database().transaction();
	for(int i=0;i<idx.count();i++)
		{
		query.bindValue(":id",idx.at(i));
		if(!query.exec())
			{
			QSqlDatabase::database().rollback();
			emit dbError(query.lastError().number(),query.lastError().text());
			return;
			}
		}
	QSqlDatabase::database().commit();
	emit prepareToModelReset();
	}

void IfDbTable::changeGroup(QList<int> idx, int group)
	{
	if(idx.count()==0){return;}
	QSqlQuery query;
	query.prepare("update hosts set groupId=:group where id=:id;");
	QSqlDatabase::database().transaction();
	for(int i=0;i<idx.count();i++)
		{
		query.bindValue(":id",idx.at(i));
		if(group==0)
			{
			query.bindValue(":group",QVariant());
			}
		else
			{
			query.bindValue(":group",group);
			}
		if(!query.exec())
			{
			QSqlDatabase::database().rollback();
			emit dbError(query.lastError().number(),query.lastError().text());
			return;
			}
		}

	QSqlDatabase::database().commit();
	emit prepareToModelReset();
	}

void IfDbTable::exportAllToCSV(QString filename, bool chId, bool chIp, bool chMask, bool chName,
							   bool chMac, bool chUser, bool chDomain, bool chLocation, bool chDhcp,
							   bool chDescription, bool header, bool numbers, QString separator)
	{
	QFile file(filename);
	if(!file.open(QIODevice::WriteOnly))
		{
		emit dbError(0,"Can't open file.");
		return;
		}

	QTextStream stream( &file );


	QString q="select * from hosts where inUse=1 order by ipAddress;";
	QSqlQuery query(q);

	if(!query.exec())
		{
		file.close();
		emit dbError(0,"Can't execute query.");
		return;
		}
	QString line;

	bool first = true;

	if(header)
		{
		first = false;
		if(chId){line.append("\"ID\""); line.append(separator);}
		if(chIp){line.append("\"IP ddress\""); line.append(separator);}
		if(chMask){line.append("\"Network Mask\""); line.append(separator);}
		if(chName){line.append("\"Host Name\""); line.append(separator);}
		if(chMac){line.append("\"MAC Address\""); line.append(separator);}
		if(chUser){line.append("\"User Name\""); line.append(separator);}
		if(chDomain){line.append("\"Domain\""); line.append(separator);}
		if(chLocation){line.append("\"Location\""); line.append(separator);}
		if(chDhcp){line.append("\"DHCP Reservation\""); line.append(separator);}
		if(chDescription){line.append("\"Description\""); line.append(separator);}
		if(line.at(line.length()-1)==separator)
			{
			line.remove(line.length()-1,1);
			}
		stream<<line;
		}

	while(query.next())
		{
		if(!first)
			{
			stream<<"\n\r";
			}
		else
			{
			first = false;
			}

		line.clear();
		if(chId){line.append(QString::number(query.value("id").toInt())); line.append(separator);}
		if(numbers)
			{
			if(chIp){line.append(QString::number(query.value("ipAddress").toInt())); line.append(separator);}
			if(chMask){line.append(QString::number(query.value("mask").toInt())); line.append(separator);}
			}
		else
			{
			if(chIp){line.append(QHostAddress(query.value("ipAddress").toInt()).toString()); line.append(separator);}
			if(chMask){line.append(QHostAddress(query.value("mask").toInt()).toString()); line.append(separator);}
			}

		if(chName)
			{
			line.append("\"");
			line.append(query.value("name").toString().replace("\"","\"\""));
			line.append("\"");
			line.append(separator);
			}

		if(chMac)
			{
			line.append("\"");
			line.append(query.value("mac").toString());
			line.append("\"");
			line.append(separator);
			}

		if(chUser)
			{
			line.append("\"");
			line.append(query.value("userName").toString().replace("\"","\"\""));
			line.append("\"");
			line.append(separator);
			}

		if(chDomain)
			{
			line.append("\"");
			line.append(query.value("domain").toString().replace("\"","\"\""));
			line.append("\"");
			line.append(separator);
			}

		if(chLocation)
			{
			line.append("\"");
			line.append(query.value("location").toString().replace("\"","\"\""));
			line.append("\"");
			line.append(separator);
			}

		if(chDhcp)
			{
			line.append("\"");
			line.append((query.value("dhcpReservation").toInt()==1)?"true":"false");
			line.append("\"");
			line.append(separator);
			}



		if(chDescription)
			{
			line.append("\"");
			line.append(query.value("description").toString().replace("\"","\"\""));
			line.append("\"");
			line.append(separator);
			}


		if(line.at(line.length()-1)==separator)
			{
			line.remove(line.length()-1,1);
			}
		stream<<line;
		}

	file.close();
	}

QList<QString> IfDbTable::getSet(QString collumn)
	{
	QString q="select "+collumn+" as col,count("+collumn+") as count from hosts group by "+collumn+" order by count desc;";
	QSqlQuery query(q);
	QList<QString> list;
	QString s;
	if(query.exec())
		{
		while(query.next())
			{
			s = query.value("col").toString().trimmed();
			if(!s.isEmpty())
				{
				list.append(s);
				}
			}
		}
	return list;
	}

QList<QString> IfDbTable::getHostNameSet()
	{
	return getSet("name");
	}

QList<QString> IfDbTable::getUserNameSet()
	{
	return getSet("userName");
	}

QList<QString> IfDbTable::getDomainSet()
	{
	return getSet("domain");
	}

QList<QString> IfDbTable::getLocationSet()
	{
	return getSet("location");
	}

QList<QString> IfDbTable::getMaskSet()
	{
	QList<QString> list;
	quint32 number = 0;
	for(int i =31; i>0;i--)
		{
		number|=1<<i;
		list.append(QHostAddress(number).toString());
		}
	return list;
	}






