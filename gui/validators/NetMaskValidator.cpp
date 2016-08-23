#include "NetMaskValidator.h"
#include <QHostAddress>
#include <QList>
#include <QString>

NetMaskValidator::NetMaskValidator(QObject *parent):QValidator(parent)
    {
    quint32 number = 0;
    for(int i =31; i>0;i--)
        {
        number|=1<<i;
        masks.append(number);
        }
    }

QValidator::State NetMaskValidator::validate(QString &value, int &) const
    {
    if(value.isEmpty()){return Intermediate;}

    QString v = value;
    v.remove(" ");

    bool intermediate = false;
    int oCount=v.count(".")+1;

    if(oCount>4){return Invalid;}
    if(oCount<4){intermediate=true;}
    for(int i=oCount;i<4;i++)
        {
        v.append(".");
        }

    QList<QString> list = v.split(".");

    for(int i=0; i<list.count();i++)
        {
        if(list.at(i).isEmpty())
            {
            list.takeAt(i);
            list.insert(i,"0");
            intermediate = true;
            }
        else if(list.at(i).count()>3)
            {
            return Invalid;
            }

        }
    qDebug()<<list;

    //find non 0 octet
    int i=oCount-1;
    while(i>=0)
        {
        if(list.at(i).toInt()==0)
            {
            i--;
            }
        else
            {
            if(list.at(i).toInt()>=0 && list.at(i).toInt()<=255)
                {
                break;
                }
            else
                {
                return Invalid;
                }
            }
        }
    i--;
    qDebug()<<i;
    for(;i>=0;i--)
        {
        if(list.at(i).toInt()!=255)
            {
            return Invalid;
            }
        }

    QString test = list.at(0)+"."+list.at(1)+"."+list.at(2)+"."+list.at(3);
    qDebug()<<test;
    QHostAddress a;
    if(!a.setAddress(test))
        {
        return Invalid;
        }
    if(!masks.contains(a.toIPv4Address()) || intermediate)
        {
        return Intermediate;
        }

    return Acceptable;
    }
