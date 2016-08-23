#include "DbFileModel.h"
#include "../global/SettingsManager.h"
#include "../database/DbFileItem.h"

#include <QDebug>

DbFileModel::DbFileModel(QObject *parent) : QAbstractListModel(parent)
    {
    }

void DbFileModel::loadData()
    {
    emit modelAboutToBeReset();
    this->source.clear();
    SettingsManager s;
    int count = s.value("databases/itemCount").toInt();
    for(int i=0; i<count;i++)
        {
        QString string = "databases/item"+QString::number(i)+"/";
        DbFileItem item;
        item.setFileName(s.value(string+"file").toString());
        item.setName(s.value(string+"name").toString());
        item.setDescription(s.value(string+"description").toString());
        this->source.append(item);
        }
    emit modelReset();
    }

int DbFileModel::rowCount(const QModelIndex &parent) const
    {
    Q_UNUSED(parent);
    return this->source.count();
    }

QVariant DbFileModel::data(const QModelIndex &index, int role) const
    {
    if (!index.isValid())
        return QVariant();

    if(index.row()>=0 && index.row()<source.count())
        {
        DbFileItem item = source.at(index.row());
        if(role == Qt::DisplayRole)
            {
            QString str;
            str.append("<b>").append(item.getName()).append("</b>");
            str.append("<br/><i>").append(item.getDescription()).append("</i>");
            return str;
            }
        if(role == Qt::ToolTipRole)
            {
            QString str;
            str.append("<b>").append(item.getFileName()).append("</b>");
            return str;
            }
        }


    return QVariant();
    }

DbFileItem DbFileModel::getDbFileItem(const QModelIndex &index) const
    {
    if (!index.isValid())
        return DbFileItem();
    if(index.row()>=0 && index.row()<source.count())
        {
        return source.at(index.row());
        }
    return DbFileItem();
    }

void DbFileModel::save()
    {
    SettingsManager s;
    s.setValue("databases/itemCount",source.count());
    for(int i =0; i<source.count();i++)
        {
        QString string = "databases/item"+QString::number(i)+"/";
        s.setValue(string+"name",source.at(i).getName());
        s.setValue(string+"file",source.at(i).getFileName());
        s.setValue(string+"description",source.at(i).getDescription());
        }
    }

void DbFileModel::addItem(QString name, QString fileName, QString description)
    {
    qDebug()<<"Add:"<<name<<fileName<<description;
    DbFileItem item;
    item.setName(name);
    item.setFileName(fileName);
    item.setDescription(description);
    source.append(item);
    save();
    loadData();
    }

void DbFileModel::updateItem(int id, QString name, QString fileName, QString description)
    {
    qDebug()<<"Update:"<<name<<fileName<<description;
    DbFileItem item;
    item.setName(name);
    item.setFileName(fileName);
    item.setDescription(description);
    source.removeAt(id);
    source.insert(id,item);
    save();
    loadData();
    }

void DbFileModel::removeItem(int id)
    {
    source.removeAt(id);
    save();
    loadData();
    }
