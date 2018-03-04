#include "ExternalAppModel.h"
#include "../global/LocalSettings.h"

#include <QtDebug>

ExternalAppModel::ExternalAppModel(QObject *parent)
	: QAbstractTableModel(parent)
	{

	}

ExternalAppModel::~ExternalAppModel()
	{
	while(this->list.count()>0)
		{
		delete this->list.takeLast();
		}
	}

void ExternalAppModel::loadData()
	{
	emit modelAboutToBeReset();
	this->list=LocalSettings().getExternalAppList();
	emit modelReset();
	}

void ExternalAppModel::saveData()
	{
	LocalSettings().setExternalAppList(this->list);
	}

QVariant ExternalAppModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
//	if(section==0 && orientation==Qt::Horizontal && role == Qt::DisplayRole)
	//	{
		return tr("Name");
	//	}
	//return QString("AAA");
	}

int ExternalAppModel::rowCount(const QModelIndex &parent) const
	{
	Q_UNUSED(parent);
	return this->list.count();
	}

int ExternalAppModel::columnCount(const QModelIndex &parent) const
	{
	Q_UNUSED(parent);
	return 1;
	}

QVariant ExternalAppModel::data(const QModelIndex &index, int role) const
	{
	if (!index.isValid())
		return QVariant();

	if(index.row()<0 || index.row() >= this->list.count() || index.column()!=0)
		return QVariant();

	if(role==Qt::DisplayRole)
		{
		return this->list.at(index.row())->getName();
		}
	return QVariant();
	}

ExternalAppItem ExternalAppModel::getItem(const QModelIndex & index)
	{
	ExternalAppItem item;
	if(index.row()>=0 && index.row()<this->list.count())
		{
		item.setName(this->list.at(index.row())->getName());
        item.setCommand(this->list.at(index.row())->getCommand());
        item.setUseInternalWindow(this->list.at(index.row())->getUseInternalWindow());
		item.setDecodeFromCp852PL(this->list.at(index.row())->getDecodeFromCp852PL());
		}
	return item;
	}

void ExternalAppModel::append(QString name, QString command, bool useInternalWindow, bool decode)
	{
	emit modelAboutToBeReset();
	ExternalAppItem *item = new ExternalAppItem();
	item->setName(name);
    item->setCommand(command);
	item->setUseInternalWindow(useInternalWindow);
	item->setDecodeFromCp852PL(decode);
	this->list.append(item);
	emit modelReset();
	}

void ExternalAppModel::update(int row, QString name, QString command, bool useInternalWindow, bool decode)
	{
	if(row>=0 && row <this->list.count())
		{
		emit modelAboutToBeReset();
		this->list.at(row)->setName(name);
        this->list.at(row)->setCommand(command);
		this->list.at(row)->setUseInternalWindow(useInternalWindow);
		this->list.at(row)->setDecodeFromCp852PL(decode);
		emit modelReset();
		}
	}

void ExternalAppModel::remove(int row)
	{
	if(row>=0 && row <this->list.count())
		{
		emit modelAboutToBeReset();
		delete this->list.takeAt(row);
		emit modelReset();
		}
	}
