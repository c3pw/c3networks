#ifndef INTERFACEITEM_H
#define INTERFACEITEM_H

#include <QObject>

class InterfaceItem : public QObject
	{
		Q_OBJECT
	public:
		explicit InterfaceItem(QObject *parent = 0);
		int getId() const;
		void setId(int value);

		quint32 getMask() const;
		void setMask(const quint32 &value);

		QString getName() const;
		void setName(const QString &value);

		QString getMac() const;
		void setMac(const QString &value);

		QString getUserName() const;
		void setUserName(const QString &value);

		QString getDomain() const;
		void setDomain(const QString &value);

		QString getDescription() const;
		void setDescription(const QString &value);

		bool getInUse() const;
		void setInUse(bool value);

		int getGroupId() const;
		void setGroupId(int value);

		QString getColor() const;
		void setColor(const QString &value);

		QString getLocation() const;
		void setLocation(const QString &value);

		quint32 getIpAddress() const;
		void setIpAddress(const quint32 &value);

		QString getGroupName() const;
		void setGroupName(const QString &value);

		bool getDhcpReservation() const;
		void setDhcpReservation(bool value);

	private:
		int id;
		quint32 ipAddress;
		quint32 mask;
		QString name;
		QString mac;
		QString userName;
		QString domain;
		QString description;
		bool inUse;
		int groupId;
		QString groupName;
		QString color;
		QString location;
		bool dhcpReservation;
	};

#endif // INTERFACEITEM_H
