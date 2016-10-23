#ifndef ADDEDITIFTYPEWINDOW_H
#define ADDEDITIFTYPEWINDOW_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
	class AddEditIfTypeWindow;
	}

class AddEditIfTypeWindow : public QDialog
	{
		Q_OBJECT

	public:
		explicit AddEditIfTypeWindow(QWidget *parent = 0);
		~AddEditIfTypeWindow();
		void editShow(int id);

	private:
		Ui::AddEditIfTypeWindow *ui;
		int id;
	signals:
		void addIfType(QString name, QPixmap icon);
		void updateIfType(int id,QString name, QPixmap icon);
	private slots:
		void on_buttonClose_clicked();
		void on_toolButton_clicked();
		void on_buttonConfirm_clicked();
	};

#endif // ADDEDITIFTYPEWINDOW_H
