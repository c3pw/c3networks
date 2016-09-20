#ifndef IFTABLESORTPROXY_H
#define IFTABLESORTPROXY_H

#include <QObject>
#include <QSortFilterProxyModel>

class IfTableSortProxy : public QSortFilterProxyModel
	{
	public:
		IfTableSortProxy(QObject *parent=0);
	protected:
		bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

		// QSortFilterProxyModel interface
	protected:
		bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

		// QAbstractItemModel interface
	public:
		QVariant data(const QModelIndex& index, int role) const;
		bool getAllColumnsFilter() const;
		void setAllColumnsFilter(bool value);

private:
		bool allColumnsFilter;
};

#endif // IFTABLESORTPROXY_H
