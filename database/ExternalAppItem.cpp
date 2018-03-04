#include "ExternalAppItem.h"

ExternalAppItem::ExternalAppItem(QObject *parent) : QObject(parent)
	{

	}

ExternalAppItem::ExternalAppItem(const ExternalAppItem & item)
	{
	this->name = item.getName();
    this->command = item.getCommand();
	this->useInternalWindow = item.getUseInternalWindow();
	this->decodeFromCp852PL = item.getDecodeFromCp852PL();
	}

const ExternalAppItem &ExternalAppItem::operator=(const ExternalAppItem & item)
	{
	this->name = item.getName();
    this->command = item.getCommand();
	this->useInternalWindow = item.getUseInternalWindow();
	this->decodeFromCp852PL = item.getDecodeFromCp852PL();
	return item;
	}

QString ExternalAppItem::getName() const
	{
	return name;
	}

void ExternalAppItem::setName(const QString & value)
	{
	name = value;
	}

QString ExternalAppItem::getCommand() const
	{
	return command;
	}

void ExternalAppItem::setCommand(const QString & value)
	{
	command = value;
	}

bool ExternalAppItem::getUseInternalWindow() const
	{
	return useInternalWindow;
	}

void ExternalAppItem::setUseInternalWindow(bool value)
	{
	useInternalWindow = value;
	}

bool ExternalAppItem::getDecodeFromCp852PL() const
	{
	return decodeFromCp852PL;
	}

void ExternalAppItem::setDecodeFromCp852PL(bool value)
	{
	decodeFromCp852PL = value;
    }

