#ifndef ADDEDITGROUPWINDOW_H
#define ADDEDITGROUPWINDOW_H

#include <QDialog>

namespace Ui { class AddEditGroupWindow; }

class AddEditGroupWindow : public QDialog
	{
		Q_OBJECT
	public:
		explicit AddEditGroupWindow(QWidget *parent = 0);
		~AddEditGroupWindow();
		void editShow(int id);
	private slots:
		void on_buttonColorDialog_clicked();
		void on_buttonCancel_clicked();
		void on_buttonApply_clicked();
	private:
		Ui::AddEditGroupWindow *ui;
		int id;
	signals:
		void addGroup(QString name, QString color);
		void updateGroup(int id,QString name, QString color);
	};

#endif // ADDEDITGROUPWINDOW_H
