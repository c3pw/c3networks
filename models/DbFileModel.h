#ifndef DBFILEMODEL_H
#define DBFILEMODEL_H

#include <QAbstractListModel>
#include "../database/DbFileItem.h"
#include <QList>

class DbFileModel : public QAbstractListModel
    {
        Q_OBJECT

    public:
        explicit DbFileModel(QObject *parent = 0);

        void loadData();

        // Basic functionality:
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        DbFileItem getDbFileItem(const QModelIndex &index) const;

    private:
        QList<DbFileItem> source;
        void save();
    signals:
        void modelAboutToBeReset();
        void modelReset();
    public slots:
        void addItem(QString name, QString fileName, QString description);
        void updateItem(int id, QString name, QString fileName, QString description);
        void removeItem(int id);
    };

#endif // DBFILEMODEL_H
