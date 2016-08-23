#include "MacValidator.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

MacValidator::MacValidator()
    {

    }

QValidator::State MacValidator::validate(QString &text, int &number) const
    {
    Q_UNUSED(number);

    qDebug()<<text;
    text.remove(":");
    text.remove("-");
    text.remove(".");

    QRegularExpression ex("^[0123456789AaBbCcDdEeFf]*$");
    QRegularExpressionMatch m = ex.match(text);

    qDebug()<<m;
    if(m.isValid() && m.hasMatch())
        {
        if(text.count()==12)
            {
            return QValidator::Acceptable;
            }
        if(text.count()<12)
            {
            return QValidator::Intermediate;
            }
        }

    return QValidator::Invalid;
    }
