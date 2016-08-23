#ifndef NETMASKVALIDATOR_H
#define NETMASKVALIDATOR_H

#include <QObject>
#include <QValidator>

class NetMaskValidator : public QValidator
    {
    Q_OBJECT
    public:
        NetMaskValidator(QObject *parent=0);
        State validate(QString &value, int &) const override;
    private:
        QList<quint32> masks;
    };

#endif // NETMASKVALIDATOR_H
