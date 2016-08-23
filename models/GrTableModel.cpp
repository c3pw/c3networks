#include "GrTableModel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "../database/GroupItem.h"

#include <QPainter>
#include <QPixmap>
#include <QIcon>

#include <QDebug>

GrTableModel::GrTableModel(QObject *parent) : QAbstractTableModel(parent)
    {
    comboMode = false;
    }

GrTableModel::~GrTableModel()
    {
    while(list.count()>0)
        {
        delete list.takeFirst();
        }
    }

void GrTableModel::setComboMode(bool mode)
    {
    comboMode = mode;
    }

int GrTableModel::rowCount(const QModelIndex & /*parent*/) const
    {
    return this->list.count();
    }

int GrTableModel::columnCount(const QModelIndex & /*parent*/) const
    {
    return 1;
    }

QVariant GrTableModel::data(const QModelIndex &index, int role) const
    {
    if(index.column()==0 && index.row()>=0 && index.row()<list.count())
        {
        if(role==Qt::DisplayRole)
            {
            return list.at(index.row())->getName();
            }
        if(role==Qt::UserRole)
            {
            return list.at(index.row())->getId();
            }
        if(role == Qt::DecorationRole)
            {
            QPixmap pixmap(16,16);
            QPainter painter(&pixmap);
            painter.fillRect(0,0,16,16,QBrush(QColor("#c0c0c0")));

            QString color = list.at(index.row())->getColor();
            if(color.isEmpty())
                {
                color = "#FFFFFF";
                }
            painter.fillRect(1,1,14,14,QBrush(QColor(color)));

            painter.end();
            return QIcon(pixmap);
            }
        }
    return QVariant();
    }

QVariant GrTableModel::headerData(int section, Qt::Orientation orientation,int role) const
    {
    if(orientation == Qt::Horizontal && role==Qt::DisplayRole)
        {
        switch(section)
            {
            case 0:{return tr("Group");}
            }
        }
    return QVariant();
    }

QModelIndex GrTableModel::index(int row, int column, const QModelIndex & /*parent*/) const
    {
    if(row >= 0 && row<list.count() && column >=0 && column<6)
        {
        return createIndex(row, column, list.at(row));
        }
    return QModelIndex();
    }

void GrTableModel::reloadData()
    {
    emit modelAboutToBeReset();


    QSqlQuery query("select * from groups order by name;");
    if(query.exec())
        {
        while(list.count()>0)
            {
            delete list.takeFirst();
            }

        if(comboMode)
            {
            GroupItem * g = new GroupItem();
            g->setId(0);
            g->setName("---");
            g->setColor("");
            this->list.append(g);
            }

        while(query.next())
            {
            GroupItem * g = new GroupItem();
            g->setId(query.value("id").toString().toInt());
            g->setName(query.value("name").toString());
            g->setColor(query.value("color").toString());
            this->list.append(g);
            }
        }
    emit modelReset();
    }

void GrTableModel::addGroup(QString name, QString color)
    {
    QSqlQuery query("insert into groups(name, color) values(:name,:color);");
    query.bindValue(0,name);
    query.bindValue(1,color);
    if(query.exec())
        {
        this->reloadData();
        }
    else
        {
        qDebug()<<query.lastError().text();
        }
    }

void GrTableModel::updateGroup(int id, QString name, QString color)
    {
    QSqlQuery query("update groups set name=:name, color=:color where id=:id;");
    query.bindValue(2,id);
    query.bindValue(0,name);
    query.bindValue(1,color);
    if(query.exec())
        {
        this->reloadData();
        }
    }

void GrTableModel::deleteGroup(int id)
    {
    QSqlQuery query("delete from groups where id=:id;");
    query.bindValue(0,id);
    if(query.exec())
        {
        this->reloadData();
        }
    }

int GrTableModel::idRow(int id)
    {
    for(int i=0; i< this->list.count(); i++)
        {
        if(list.at(i)->getId() == id)
            {
            return i;
            }
        }
    return 0;
    }
