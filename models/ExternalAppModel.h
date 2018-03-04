#ifndef EXTERNALAPPMODEL_H
#define EXTERNALAPPMODEL_H

#include <QAbstractTableModel>
#include "../database/ExternalAppItem.h"
#include <QList>

class ExternalAppModel : public QAbstractTableModel
	{
		Q_OBJECT
	public:
		explicit ExternalAppModel(QObject *parent = 0);
		~ExternalAppModel();
		void loadData();
		void saveData();

		// Header:
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

		// Basic functionality:
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		int columnCount(const QModelIndex &parent = QModelIndex()) const override;

		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
		ExternalAppItem getItem(const QModelIndex &index);
	public slots:
        void append(QString name, QString command, bool useInternalWindow, bool decode);
        void update(int row, QString name, QString command, bool useInternalWindow, bool decode);
		void remove(int row);
	signals:
		void modelAboutToBeReset();
		void modelReset();

	private:
		QList <ExternalAppItem*> list;
	};

#endif // AXTERNALAPPMODEL_H
