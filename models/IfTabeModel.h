#ifndef IFTABEMODEL_H
#define IFTABEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QIcon>
#include "../database/InterfaceItem.h"

class IfTabeModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        IfTabeModel(QObject *parent=0);
		static const int COL_COUNT = 9;
		enum COL_TYPE {IP,NAME,IFTYPE,DHCPRESERVATION,MAC,USERNAME,LOCATION,HOSTDOMAIN,DESCRIPTION};
    private:
        bool dataLoading;
        QList<InterfaceItem*> interfaces;
        QVariant dataDisplayRole(const QModelIndex &index) const;
        QVariant dataDecorationRole(const QModelIndex &index) const;
        QVariant dataForegroundRole(const QModelIndex &index) const;
        QVariant dataToolTipRole(const QModelIndex &index) const;
        QVariant dataTextAlignmentRole(const QModelIndex &index) const;
        QIcon dhcpOk;
		QMap<int,QPixmap> interfaceIcons;
    public:
        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        QPointer<InterfaceItem> getInterfaceItem(QModelIndex index);
    public slots:
        void loadData();
		void loadInterfaceIcons();
    signals:
        void modelAboutToBeReset();
        void modelReset();
    };

#endif // IFTABEMODEL_H
