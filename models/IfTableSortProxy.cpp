#include "IfTableSortProxy.h"
#include <QHostAddress>

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

IfTableSortProxy::IfTableSortProxy(QObject *parent):QSortFilterProxyModel(parent)
    {

    }

bool IfTableSortProxy::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
    {
    if(source_left.isValid() && source_right.isValid())
        {
        QVariant dataLeft = sourceModel()->data(source_left);
        QVariant dataRight = sourceModel()->data(source_right);

        if(this->sortColumn() == 0)
            {
            return (QHostAddress(dataLeft.toString()).toIPv4Address() < QHostAddress(dataRight.toString()).toIPv4Address());
            }
        else
            {
            /*
            QRegExp ex("\\d+$");
            QString sl =dataLeft.toString();
            QString sr =dataRight.toString();

            int il = ex.indexIn(sl);
            int ir = ex.indexIn(sr);

            if(il !=-1 && ir !=-1)
                {
                if(sl.mid(0,il) == sr.mid(0,ir))
                    {
                    int nl = sl.mid(il,sl.count()-il).toInt();
                    int nr = sr.mid(ir,sr.count()-ir).toInt();
                    return nl<nr;
                    }
                }

*/

            return (QString::localeAwareCompare(dataLeft.toString(), dataRight.toString()) <0);
            }
        }
    return false;
    }
