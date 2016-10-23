#ifndef DATABASEUPDATEWINDOW_H
#define DATABASEUPDATEWINDOW_H

#include <QDialog>
#include <QMovie>
#include <QThread>
#include "../../database/DatabaseUpdater.h"
#include "../../database/DbFileItem.h"

namespace Ui {
	class DatabaseUpdateWindow;
	}

class DbFileItem;
class DatabaseUpdater;

class DatabaseUpdateWindow : public QDialog
	{
		Q_OBJECT

	public:
		explicit DatabaseUpdateWindow(QWidget *parent = 0);
		~DatabaseUpdateWindow();
		void update(DbFileItem &item);
	public slots:
		void setMaxValue(int max);
		void setValue(int value);
		void canBeClosed();
		void error(QString);
	private slots:
		void on_closeButton_clicked();

	private:
		Ui::DatabaseUpdateWindow *ui;
		QMovie movie;
		DatabaseUpdater *updater;
		QThread thread;
	};

#endif // DATABASEUPDATEWINDOW_H
