#include "IfTableSortProxy.h"
#include <QHostAddress>

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QColor>

IfTableSortProxy::IfTableSortProxy(QObject *parent):QSortFilterProxyModel(parent)
	{
	this->allColumnsFilter = false;
	}

bool IfTableSortProxy::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
	{
	if(source_left.isValid() && source_right.isValid())
		{
		QVariant dataLeft = sourceModel()->data(source_left);
		QVariant dataRight = sourceModel()->data(source_right);

		if(this->sortColumn() == 0)
			{
			return (QHostAddress(dataLeft.toString()).toIPv4Address() < QHostAddress(dataRight.toString()).toIPv4Address());
			}
		else
			{
			return (QString::localeAwareCompare(dataLeft.toString(), dataRight.toString()) <0);
			}
		}
	return false;
	}

bool IfTableSortProxy::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
	{
	if(allColumnsFilter)
		{
		if(this->sourceModel()!=NULL)
			{
			qDebug()<<"Filter columns: "<<this->sourceModel()->columnCount()<<" Filter regexp: "<<filterRegExp();
			int col = this->sourceModel()->columnCount();
			for(int i=0; i<col;i++)
				{
				QModelIndex index = sourceModel()->index(source_row, i, source_parent);
				if(index.data().toString().contains(this->filterRegExp()))
					{
					return true;
					}
				}
			return false;
			}
		}
	else
		{
		QModelIndex index = sourceModel()->index(source_row, this->filterKeyColumn(), source_parent);
		return index.data().toString().contains(this->filterRegExp());
		}
	return true;
	}

QVariant IfTableSortProxy::data(const QModelIndex& index, int role) const
	{
	QVariant data = this->sourceModel()->data(this->mapToSource(index),role);
	if(allColumnsFilter)
		{
		QString pattern = this->filterRegExp().pattern();
		pattern = pattern.remove("\^\.\*");
		pattern = pattern.remove("\.\*\$");
		if(role == Qt::BackgroundColorRole && !pattern.isEmpty())
			{

			QString text = this->sourceModel()->data(this->mapToSource(index),Qt::DisplayRole).toString();
			if(text.contains(this->filterRegExp()))
				{
				data = QColor(0, 255, 0, 50);
				}
			}
		}
	return data;
	}

bool IfTableSortProxy::getAllColumnsFilter() const
{
	return allColumnsFilter;
}

void IfTableSortProxy::setAllColumnsFilter(bool value)
{
	allColumnsFilter = value;
}
