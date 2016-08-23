#ifndef DBFILEITEM_H
#define DBFILEITEM_H

#include <QObject>
#include <QSqlDatabase>

class DbFileItem : public QObject
    {
        Q_OBJECT
    public:
        DbFileItem(QObject *parent = 0);
        DbFileItem(const DbFileItem &source, QObject *parent = 0);
        void operator =(const DbFileItem &source);

        static const int version = 3;

        QString getFileName() const;
        void setFileName(const QString &value);
        QString getDescription() const;
        void setDescription(const QString &value);
        QString getName() const;
        void setName(const QString &value);

        bool openDbConnection();
        bool analizeFile(QWidget* parent=0);
    private:
        QString fileName;
        QString description;
        QString name;
        bool update(QSqlDatabase db, int version);
        bool executeScript(QSqlDatabase db, QString scriptFile);
    };

#endif // DBFILEITEM_H
