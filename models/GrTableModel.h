#ifndef GROUPSTABLEMODEL_H
#define GROUPSTABLEMODEL_H

#include <QAbstractTableModel>
#include "../database/GroupItem.h"

class GrTableModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit GrTableModel(QObject *parent = 0);
        ~GrTableModel();
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation,int role) const;
        QModelIndex index(int row, int column, const QModelIndex &parent) const;
        int idRow(int id);
        void setComboMode(bool mode);
    private:
        QList<GroupItem*> list;
        bool comboMode;

    public slots:
        void reloadData();
        void addGroup(QString name, QString color);
        void updateGroup(int id, QString name, QString color);
        void deleteGroup(int id);
    signals:
        void modelAboutToBeReset();
        void modelReset();
    };

#endif // GROUPSTABLEMODEL_H
