#include "LocalSettings.h"
#include <QColor>

LocalSettings::LocalSettings():QSettings(QSettings::IniFormat,QSettings::UserScope,"pworwag.com.pl","c3networks")
	{
	if(!allKeys().contains("rememberFilterMode"))
		{
		setValue("rememberFilterMode",true);
		}
	if(!allKeys().contains("filterHilightColor"))
		{
		setValue("filterHilightColor",QColor(0, 255, 0, 50));
		}
	if(!allKeys().contains("actionsCounter"))
		{
		setValue("actionsCounter",0);
		}
	}

QList<ExternalAppItem *> LocalSettings::getExternalAppList()
	{
	int count = this->value("actionsCounter").toInt();
	QList<ExternalAppItem*> list;
	for(int i=0;  i<count; i++)
		{
		ExternalAppItem *item = new ExternalAppItem();
		item->setName(this->value(QString("Actions/action_").append(QString::number(i)).append("_name")).toString());
        item->setCommand(this->value(QString("Actions/action_").append(QString::number(i)).append("_command")).toString());
		item->setUseInternalWindow(this->value(QString("Actions/action_").append(QString::number(i)).append("_uiw")).toBool());
		item->setDecodeFromCp852PL(this->value(QString("Actions/action_").append(QString::number(i)).append("_cp852pl")).toBool());
		list.append(item);
		}


    qSort(list.begin(),list.end(),exAppLessThan);

	return list;
	}

void LocalSettings::setExternalAppList(QList<ExternalAppItem *> list)
	{
	this->setValue("actionsCounter",list.count());
	for(int i=0;i<list.count();i++)
		{
		this->setValue(QString("Actions/action_").append(QString::number(i)).append("_name"),list.at(i)->getName());
        this->setValue(QString("Actions/action_").append(QString::number(i)).append("_command"),list.at(i)->getCommand());
		this->setValue(QString("Actions/action_").append(QString::number(i)).append("_uiw"),list.at(i)->getUseInternalWindow());
		this->setValue(QString("Actions/action_").append(QString::number(i)).append("_cp852pl"),list.at(i)->getDecodeFromCp852PL());
    }
}

bool exAppLessThan(const ExternalAppItem *i1, const ExternalAppItem *i2)
{
    return i1->getName()<=i2->getName();
}
