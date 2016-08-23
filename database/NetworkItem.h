#ifndef NETWORKITEM_H
#define NETWORKITEM_H

#include <QObject>

class NetworkItem : public QObject
    {
        Q_OBJECT
    public:
        explicit NetworkItem(QObject *parent = 0);
    quint32 getIpAddress() const;
    void setIpAddress(const quint32 &value);

    quint32 getMask() const;
    void setMask(const quint32 &value);

    private:
        quint32 ipAddress;
        quint32 mask;
    };

#endif // NETWORKITEM_H
