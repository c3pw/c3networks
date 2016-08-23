#ifndef IPVALIDATOR_H
#define IPVALIDATOR_H

#include <QObject>
#include <QValidator>

class IpValidator : public QValidator
    {
    Q_OBJECT
    public:
        IpValidator(QObject* parent=0);

        // QValidator interface
    public:
        State validate(QString &value, int &number) const override;
};

#endif // IPVALIDATOR_H
