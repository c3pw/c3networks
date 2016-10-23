#ifndef INTERFACETYPEITEM_H
#define INTERFACETYPEITEM_H

#include <QObject>
#include <QString>
#include <QPixmap>

class InterfaceTypeItem : public QObject
	{
		Q_OBJECT
	public:
		explicit InterfaceTypeItem(QObject *parent = 0);
		InterfaceTypeItem(InterfaceTypeItem &source, QObject *parent = 0);
		void operator =(const InterfaceTypeItem &source);
		InterfaceTypeItem(int id, QString name, QPixmap icon = QPixmap(), QObject *parent =0);

		int getId() const;
		void setId(int value);

		QString getName() const;
		void setName(const QString& value);

		QPixmap getIcon() const;
		void setIcon(const QPixmap& value);

	private:
		int id;
		QString name;
		QPixmap icon;
	};

#endif // INTERFACETYPEITEM_H
