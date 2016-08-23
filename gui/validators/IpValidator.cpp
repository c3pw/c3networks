#include "IpValidator.h"
#include <QDebug>

#include <QHostAddress>
#include <QStringList>

IpValidator::IpValidator(QObject *parent):QValidator(parent)
    {
    }

QValidator::State IpValidator::validate(QString &value, int &number) const
    {
    Q_UNUSED(number)
    value.remove(" ");
    QString v = value;
    if(v.isEmpty()){return Intermediate;}
    QList<QString> list = v.split(".");
    if(list.count()>4){return Invalid;}
    if(v.at(v.count()-1)=='.'){list.takeLast();}
    for(int i =0; i<list.count();i++)
        {
        if(list.at(i).count()>3){return Invalid;}
        bool ok=false;
        int number = list.at(i).toInt(&ok);
        if(!ok){return Invalid;}
        if(number<0 || number >=255){return Invalid;}
        }
    return Acceptable;
    }
