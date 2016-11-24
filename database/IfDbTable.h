#ifndef IFDBTABLE_H
#define IFDBTABLE_H

#include <QObject>
#include <QList>

class IfDbTable : public QObject
	{
		Q_OBJECT
	public:
		explicit IfDbTable(QObject *parent = 0);
	signals:
		void dbError(int number, QString text);
		void prepareToModelReset();
	public slots:
		void addInterface(quint32 ipAddress, quint32 mask,
						  QString name, QString mac, QString userName,
						  QString domain,QString description, bool inUse,
						  int groupId, QString location, bool dhcpReservation,int interfaceId,QString switchPort);
		void addInterfaces(quint32 from, quint32 to, quint32 mask,
						   int groupId);
		void updateInterface(int id, quint32 ipAddress, quint32 mask,
							 QString name, QString mac, QString userName,
							 QString domain, QString description, bool inUse,
							 int groupId, QString location, bool dhcpReservation, int interfaceId,QString switchPort);
		void deleteInterfaces(QList<int> idx);
		void changeGroup(QList<int> idx,int group);
		void exportAllToCSV(QString filename,bool chId, bool chIp, bool chMask, bool chName, bool chMac,
							bool chUser, bool chDomain, bool chLocation, bool chDhcp, bool chDescription,
							bool header, bool numbers, QString separator);
	private:
		static QList<QString> getSet(QString collumn);
	public:
		static QList<QString> getHostNameSet();
		static QList<QString> getUserNameSet();
		static QList<QString> getDomainSet();
		static QList<QString> getLocationSet();
		static QList<QString> getMaskSet();
	};

#endif // IFDBTABLE_H
