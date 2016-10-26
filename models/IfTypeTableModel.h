#ifndef IFTYPETABLEMODEL_H
#define IFTYPETABLEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "../database/InterfaceTypeItem.h"

class IfTypeTableModel : public QAbstractListModel
	{
		Q_OBJECT

	public:
		explicit IfTypeTableModel(QObject *parent = 0);

		// Header:
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

		// Basic functionality:
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;

		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		InterfaceTypeItem* getItem(int index);
		void setComboMode(bool mode);
		int idRow(int id);
	public slots:
		void loadData();
		void insert(QString name, QPixmap icon);
		void update(int id, QString name, QPixmap icon);
		void remove(int id);
	signals:
		void modelAboutToBeReset();
		void modelReset();
	private:
		QList<InterfaceTypeItem*> source;
		bool comboMode;
	};

#endif // IFTYPETABLEMODEL_H
