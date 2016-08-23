#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QString>

class GroupItem
    {
    public:
        GroupItem();
        int getId() const;
        void setId(int value);

        QString getName() const;
        void setName(const QString &value);

        QString getColor() const;
        void setColor(const QString &value);

private:
        int id;
        QString name;
        QString color;

};

#endif // GROUP_H
