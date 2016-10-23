#include "NetworkItem.h"

NetworkItem::NetworkItem(QObject *parent) : QObject(parent)
	{

	}

quint32 NetworkItem::getIpAddress() const
	{
	return ipAddress;
	}

void NetworkItem::setIpAddress(const quint32 &value)
	{
	ipAddress = value;
	}

quint32 NetworkItem::getMask() const
	{
	return mask;
	}

void NetworkItem::setMask(const quint32 &value)
	{
	mask = value;
	}
