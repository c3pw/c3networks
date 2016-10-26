#include "IfTypeTableModel.h"
#include <QSqlQuery>
#include <QPixmap>

#include <QDebug>
#include <QSqlError>
#include <QBuffer>

IfTypeTableModel::IfTypeTableModel(QObject *parent)
	: QAbstractListModel(parent)
	{
	this->comboMode = false;
	}

QVariant IfTypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
	if(orientation==Qt::Horizontal && section==0 && role==Qt::DisplayRole)
		{
		return tr("Interface type");
		}
	return QVariant();
	}

int IfTypeTableModel::rowCount(const QModelIndex &parent) const
	{
	Q_UNUSED(parent)
	return source.count();
	}

QVariant IfTypeTableModel::data(const QModelIndex &index, int role) const
	{
	if((index.row()>=0) && (index.row()<source.count()) && (index.column()==0))
		{
		if(role==Qt::DisplayRole)
			{
			return source.at(index.row())->getName();
			}
		if(role==Qt::UserRole)
			{
			return source.at(index.row())->getId();
			}
		if(role==Qt::DecorationRole)
			{
			QPixmap icon = source.at(index.row())->getIcon();
			if(icon.isNull())
				{
				icon = QPixmap(16,16);
				icon.fill(Qt::transparent);
				}
			return icon;
			}
		}
	return QVariant();
	}

InterfaceTypeItem*IfTypeTableModel::getItem(int index)
	{
	if(index>=0 && index<source.count())
		{
		return source.at(index);
		}
	return NULL;
	}

void IfTypeTableModel::setComboMode(bool mode)
	{
	this->comboMode = mode;
	}

int IfTypeTableModel::idRow(int id)
	{
	for(int i=0; i< this->source.count(); i++)
		{
		if(source.at(i)->getId() == id)
			{
			return i;
			}
		}
	return 0;
	}

void IfTypeTableModel::loadData()
	{
	emit modelAboutToBeReset();
	source.clear();
	if(comboMode)
		{
		QPixmap p;
		p.scaled(16,16);
		p.fill(Qt::transparent);
		source.append(new InterfaceTypeItem(0,"---",p));
		}
	QSqlQuery q("select * from interfaces order by name;");
	if(q.exec())
		{
		QPixmap p;
		while(q.next())
			{
			p.loadFromData(q.value("icon").toByteArray());
			source.append(new InterfaceTypeItem(q.value("id").toInt(),q.value("name").toString(),p));
			}
		}
	emit modelReset();
	}

void IfTypeTableModel::insert(QString name, QPixmap icon)
	{
	qDebug()<<"insert"<<name<<icon;

	// Preparation of our QPixmap
	QByteArray bArray;
	QBuffer buffer(&bArray);
	buffer.open(QIODevice::WriteOnly);
	icon.save(&buffer, "PNG");
	buffer.close();

	QSqlQuery q("insert into interfaces (name,icon) values(:name,:icon);");
	q.bindValue(0,name);
	q.bindValue(1,bArray);
	if(q.exec())
		{
		loadData();
		}
	}

void IfTypeTableModel::update(int id, QString name, QPixmap icon)
	{
	// Preparation of our QPixmap
	QByteArray bArray;
	QBuffer buffer(&bArray);
	buffer.open(QIODevice::WriteOnly);
	icon.save(&buffer, "PNG");
	buffer.close();

	QSqlQuery q("update interfaces set name=:name,icon=:icon where id=:id;");
	q.bindValue(2,id);
	q.bindValue(0,name);
	q.bindValue(1,bArray);
	if(q.exec())
		{
		loadData();
		}

	}

void IfTypeTableModel::remove(int id)
	{
	QSqlQuery q("delete from interfaces where id=:id;");
	q.bindValue(0,id);
	if(q.exec())
		{
		loadData();
		}
	}
