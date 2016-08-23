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
};

#endif // IFTABLESORTPROXY_H
