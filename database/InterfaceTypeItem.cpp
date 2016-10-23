#include "InterfaceTypeItem.h"

InterfaceTypeItem::InterfaceTypeItem(QObject *parent) : QObject(parent)
	{

	}

InterfaceTypeItem::InterfaceTypeItem(InterfaceTypeItem& source, QObject* parent)
	{
	this->id = source.id;
	this->name = source.name;
	this->icon = source.icon;
	}

void InterfaceTypeItem::operator =(const InterfaceTypeItem& source)
	{
	this->id = source.id;
	this->name = source.name;
	this->icon = source.icon;
	}

InterfaceTypeItem::InterfaceTypeItem(int id, QString name, QPixmap icon, QObject* parent) : QObject(parent)
	{
	this->id=id;
	this->name=name;
	this->icon = icon;
	}

int InterfaceTypeItem::getId() const
	{
	return id;
	}

void InterfaceTypeItem::setId(int value)
	{
	id = value;
	}

QString InterfaceTypeItem::getName() const
	{
	return name;
	}

void InterfaceTypeItem::setName(const QString& value)
	{
	name = value;
	}

QPixmap InterfaceTypeItem::getIcon() const
	{
	return icon;
	}

void InterfaceTypeItem::setIcon(const QPixmap& value)
	{
	icon = value;
	}
