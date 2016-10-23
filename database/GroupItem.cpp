#include "GroupItem.h"

GroupItem::GroupItem()
	{
	}

int GroupItem::getId() const
	{
	return id;
	}

void GroupItem::setId(int value)
	{
	id = value;
	}

QString GroupItem::getName() const
	{
	return name;
	}

void GroupItem::setName(const QString &value)
	{
	name = value;
	}

QString GroupItem::getColor() const
	{
	return color;
	}

void GroupItem::setColor(const QString &value)
	{
	color = value;
	}



