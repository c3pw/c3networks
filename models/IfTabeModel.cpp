#include "IfTabeModel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QPointer>
#include <QHostAddress>
#include <QPixmap>
#include <QPainter>
#include <QIcon>
#include <QDebug>

IfTabeModel::IfTabeModel(QObject *parent):QAbstractTableModel(parent)
    {
    dataLoading = false;
    dhcpOk = QIcon(":/icons/dhcp-ok.png");
    }

QVariant IfTabeModel::dataDisplayRole(const QModelIndex &index) const
    {
    if(index.row()>=0 && index.row()<interfaces.count()&& index.column()>=0 && index.column()<COL_COUNT)
        {
        QPointer<InterfaceItem> item = static_cast<InterfaceItem*>(interfaces.at(index.row()));
        if(!item.isNull())
            {
            switch(index.column())
                {
                case IP:{return QHostAddress(item->getIpAddress()).toString();}
                case NAME:{return item->getName();}
                case MAC:{return item->getMac().toUpper();}
                //case DHCPRESERVATION:{return item->getDhcpReservation()?tr("YES"):tr("NO");}
                case USERNAME:{return item->getUserName();}
                case LOCATION:{return item->getLocation();}
                case HOSTDOMAIN:{return item->getDomain();}
                case DESCRIPTION:{return item->getDescription();}
				case IFTYPE:{return item->getInterfaceTypeName();}
                }
            }
        }
    return QVariant();
    }

QVariant IfTabeModel::dataDecorationRole(const QModelIndex &index) const
    {
	if(index.row()>=0 && index.row()<interfaces.count())
        {
		QPointer<InterfaceItem> item = static_cast<InterfaceItem*>(interfaces.at(index.row()));
		if(index.column()==IP)
			{
			if(!item.isNull())
				{
				QPixmap pixmap(16,16);
				QPainter painter(&pixmap);
				painter.fillRect(0,0,16,16,QBrush(QColor("#c0c0c0")));

				QString color = item->getColor();
				if(color.isEmpty()){color="#FFF";}
				painter.fillRect(1,1,14,14,QBrush(QColor(color)));
				painter.end();
				return pixmap;
				}
			}
		if(index.column()==IFTYPE)
			{
			if(!item.isNull() && (this->interfaceIcons.keys().contains(item->getInterfaceType())))
				{
				return this->interfaceIcons.value(item->getInterfaceType());
				}
			else
				{
				QPixmap pixmap(16,16);
				pixmap.fill(Qt::transparent);
				return pixmap;
				}

			}
        }

    if(index.row()>=0 && index.row()<interfaces.count()&& index.column()==DHCPRESERVATION)
        {
        QPointer<InterfaceItem> item = static_cast<InterfaceItem*>(interfaces.at(index.row()));

        if(!item.isNull())
            {
            if(item->getDhcpReservation())
                {
                return dhcpOk;
                }
            }
        }
    return QVariant();
    }

QVariant IfTabeModel::dataForegroundRole(const QModelIndex &index) const
    {
    if(index.row()>=0 && index.row()<interfaces.count()&& index.column()>=0 && index.column()<COL_COUNT)
        {
        QPointer<InterfaceItem> item = static_cast<InterfaceItem*>(interfaces.at(index.row()));
        if(!item.isNull())
            {
            if(!item->getInUse())
                {
                return QColor("#CCC");
                }
            }
        }
    return QVariant();
    }

QVariant IfTabeModel::dataToolTipRole(const QModelIndex &index) const
    {
    if(index.row()>=0 && index.row()<interfaces.count()&& index.column()==0)
        {
        QPointer<InterfaceItem> item = static_cast<InterfaceItem*>(interfaces.at(index.row()));

        if(!item.isNull())
            {
            return tr("Group: ")+item->getGroupName();
            }
        }
    return QVariant();
    }

QVariant IfTabeModel::dataTextAlignmentRole(const QModelIndex &index) const
    {
    if(index.column()==DHCPRESERVATION)
        {
        return Qt::AlignCenter;
        }
    return QVariant();
    }

int IfTabeModel::rowCount(const QModelIndex &parent) const
    {
    Q_UNUSED(parent)
    if(dataLoading){return 0;}
    return interfaces.count();
    }

int IfTabeModel::columnCount(const QModelIndex &parent) const
    {
    Q_UNUSED(parent)
    if(dataLoading){return 0;}
    return COL_COUNT;
    }

QVariant IfTabeModel::data(const QModelIndex &index, int role) const
    {
    if(dataLoading){QVariant();}
    switch(role)
        {
        case Qt::DisplayRole: {return dataDisplayRole(index);}
        case Qt::DecorationRole: {return dataDecorationRole(index);}
        case Qt::ForegroundRole: {return dataForegroundRole(index);}
        case Qt::ToolTipRole: {return dataToolTipRole(index);}
		case Qt::TextAlignmentRole: {return dataTextAlignmentRole(index);}
        }
    return QVariant();
    }

QVariant IfTabeModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
    if(orientation==Qt::Horizontal && role == Qt::DisplayRole)
        {
        switch(section)
            {
            case IP:{return tr("Ip Address");}
            case NAME:{return tr("Host Name");}
            case DHCPRESERVATION:{return tr("DHCP");}
            case MAC:{return tr("Mac Address");}
            case USERNAME:{return tr("User Name");}
            case LOCATION:{return tr("Location");}
			case HOSTDOMAIN:{return tr("Domain");}
			case DESCRIPTION:{return tr("Description");}
			case IFTYPE:{return tr("Interface type");}
            }
        }
    return QVariant();
}

QPointer<InterfaceItem> IfTabeModel::getInterfaceItem(QModelIndex index)
    {
    qDebug()<<"IfTabeModel::getInterfaceItem("<<index<<");";
    if(dataLoading){QPointer<InterfaceItem>(NULL);}
    if(index.row()>=0 && index.row()<interfaces.count()&& index.column()==0)
        {
        return QPointer<InterfaceItem>(interfaces.at(index.row()));
        }
    return QPointer<InterfaceItem>(NULL);
    }

void IfTabeModel::loadData()
    {
    qDebug()<<"IfTabeModel::loadData()";
    emit this->modelAboutToBeReset();
    dataLoading = true;


	loadInterfaceIcons();

    qDebug()<<"\tcleaning";
    while(!interfaces.isEmpty())
        {
        delete interfaces.takeLast();
        }
    qDebug()<<"\tloading data from database";
    QSqlQuery query;
    query.prepare("select hosts.id as id, hosts.ipAddress as ipAddress,hosts.dhcpReservation as dhcpReservation, hosts.mask as mask, hosts.name as name, "
                  "hosts.mac as mac, hosts.userName as userName, hosts.domain as domain, hosts.description as description, "
                  "hosts.inUse as inUse, hosts.groupId as groupId, hosts.location as location, groups.name as groupName, "
				  "groups.color as color, hosts.interfaceId as interfaceId, interfaces.name as interfaceName "
				  "from hosts left join groups on hosts.groupId = groups.id "
				  "left join interfaces on hosts.interfaceId = interfaces.id order by hosts.ipAddress;");
    if(query.exec())
        {
        while(query.next())
            {
            InterfaceItem *item = new InterfaceItem();
            item->setId(query.value("id").toInt());
            item->setIpAddress(query.value("ipAddress").toInt());
            item->setDhcpReservation(query.value("dhcpReservation").toInt() !=0);
            item->setMask(query.value("mask").toInt());
            item->setName(query.value("name").toString());
            item->setMac(query.value("mac").toString().toUpper());
            item->setUserName(query.value("userName").toString());
            item->setDomain(query.value("domain").toString());
            item->setDescription(query.value("description").toString());
            item->setInUse(query.value("inUse").toInt()==1);
            item->setGroupId(query.value("groupId").toInt());
            item->setGroupName(query.value("groupName").toString());
            item->setLocation(query.value("location").toString());
            item->setColor(query.value("color").toString());
			item->setInterfaceType(query.value("interfaceId").toInt());
			item->setInterfaceTypeName(query.value("interfaceName").toString());
            interfaces.append(item);
            }
        }
    else
        {
        qDebug()<<query.lastError().text();
		qDebug()<<query.lastQuery();
        }


    dataLoading = false;
    qDebug()<<"\tloaded items: "<<interfaces.count();
    emit modelReset();

	}

void IfTabeModel::loadInterfaceIcons()
	{
	this->interfaceIcons.clear();
	QSqlQuery q("select * from interfaces order by id;");
	if(q.exec())
		{
		while(q.next())
			{QPixmap p;
			p.loadFromData(q.value("icon").toByteArray());
			this->interfaceIcons.insert(q.value("id").toInt(),p);
			}
		}
	}
