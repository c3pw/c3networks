#ifndef IFTYPEMANAGERWINDOW_H
#define IFTYPEMANAGERWINDOW_H

#include <QDialog>
#include "../../models/IfTypeTableModel.h"

namespace Ui {
	class IfTypeManagerWindow;
	}

class IfTypeManagerWindow : public QDialog
	{
		Q_OBJECT

	public:
		explicit IfTypeManagerWindow(QWidget *parent = 0);
		~IfTypeManagerWindow();

	private slots:
		void on_buttonClose_clicked();

		void on_buttonAdd_clicked();

		void on_buttonEdit_clicked();

		void on_buttonRemove_clicked();

	private:
		Ui::IfTypeManagerWindow *ui;
		IfTypeTableModel *model;
	signals:
		void deleteIfType(int id);
	};

#endif // IFTYPEMANAGERWINDOW_H
