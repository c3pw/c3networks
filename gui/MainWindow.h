#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "../database/IfDbTable.h"
#include "../models/IfTabeModel.h"
#include "../models/IfTableSortProxy.h"


namespace Ui {
	class MainWindow;
	}

class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	public slots:
		void prepareToModelReset();
	private slots:
		void on_ifTableFilterEdit_textChanged(const QString &arg1);

		void on_buttonRefresh_clicked();

		void on_pushButton_clicked();

		void on_buttonEditHost_clicked();

		void on_buttonGroupsManager_clicked();

		void on_ifTable_doubleClicked(const QModelIndex &index);

		void on_actionAbout_Application_triggered();

		void on_actionAbout_QT_triggered();

		void on_actionSettings_triggered();

		void on_buttonRemoveHost_clicked();

		void on_ifTable_customContextMenuRequested(const QPoint &pos);

		void on_actionChangeGroup_triggered();

		void on_pushAddRange_clicked();

		void on_actionExport_triggered();

		void on_ifTableFilterModeButton_toggled(bool checked);

		void on_ifTableFilterBox_activated(int index);

		void on_actionPing_triggered();

		void on_actionShowArp_triggered();

		void on_actionDNS1_triggered();

		void on_actionDNS2_triggered();

	private:
		Ui::MainWindow *ui;
		IfDbTable ifDbTable;
		IfTabeModel *tableModel;
		IfTableSortProxy *tableProxy;
		QMenu rightButtonMenu;

		void executeApp(QString app, QStringList params);
	signals:
		void deleteInterfaces(QList<int> idx);
	};

#endif // MAINWINDOW_H
