#ifndef HTMLHELPER_H
#define HTMLHELPER_H

#include <QStyledItemDelegate>

class HtmlHelper : public QStyledItemDelegate
    {
    public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    };

#endif // HTMLHELPER_H
