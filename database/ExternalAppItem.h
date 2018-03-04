#ifndef EXTERNALAPPITEM_H
#define EXTERNALAPPITEM_H

#include <QObject>

class ExternalAppItem : public QObject
	{
		Q_OBJECT
	public:
		explicit ExternalAppItem(QObject *parent = 0);
		ExternalAppItem(const ExternalAppItem & item);
		const ExternalAppItem& operator=(const ExternalAppItem & item);
		QString getName() const;
		void setName(const QString & value);

		QString getCommand() const;
		void setCommand(const QString & value);

		bool getUseInternalWindow() const;
		void setUseInternalWindow(bool value);

		bool getDecodeFromCp852PL() const;
		void setDecodeFromCp852PL(bool value);

private:
        QString name;
        QString command;
		bool useInternalWindow;
		bool decodeFromCp852PL;
	};

#endif // EXTERNALAPPITEM_H
