#include "InterfaceItem.h"

InterfaceItem::InterfaceItem(QObject *parent) : QObject(parent)
	{

	}

int InterfaceItem::getId() const
	{
	return id;
	}

void InterfaceItem::setId(int value)
	{
	id = value;
	}

quint32 InterfaceItem::getMask() const
	{
	return mask;
	}

void InterfaceItem::setMask(const quint32 &value)
	{
	mask = value;
	}

QString InterfaceItem::getName() const
	{
	return name;
	}

void InterfaceItem::setName(const QString &value)
	{
	name = value;
	}

QString InterfaceItem::getMac() const
	{
	return mac;
	}

void InterfaceItem::setMac(const QString &value)
	{
	mac = value;
	}

QString InterfaceItem::getUserName() const
	{
	return userName;
	}

void InterfaceItem::setUserName(const QString &value)
	{
	userName = value;
	}

QString InterfaceItem::getDomain() const
	{
	return domain;
	}

void InterfaceItem::setDomain(const QString &value)
	{
	domain = value;
	}

QString InterfaceItem::getDescription() const
	{
	return description;
	}

void InterfaceItem::setDescription(const QString &value)
	{
	description = value;
	}

bool InterfaceItem::getInUse() const
	{
	return inUse;
	}

void InterfaceItem::setInUse(bool value)
	{
	inUse = value;
	}

int InterfaceItem::getGroupId() const
	{
	return groupId;
	}

void InterfaceItem::setGroupId(int value)
	{
	groupId = value;
	}

QString InterfaceItem::getColor() const
	{
	return color;
	}

void InterfaceItem::setColor(const QString &value)
	{
	color = value;
	}

QString InterfaceItem::getLocation() const
	{
	return location;
	}

void InterfaceItem::setLocation(const QString &value)
	{
	location = value;
	}

quint32 InterfaceItem::getIpAddress() const
	{
	return ipAddress;
	}

void InterfaceItem::setIpAddress(const quint32 &value)
	{
	ipAddress = value;
	}

QString InterfaceItem::getGroupName() const
	{
	return groupName;
	}

void InterfaceItem::setGroupName(const QString &value)
	{
	groupName = value;
	}

bool InterfaceItem::getDhcpReservation() const
	{
	return dhcpReservation;
	}

void InterfaceItem::setDhcpReservation(bool value)
	{
	dhcpReservation = value;
	}
