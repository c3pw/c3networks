#ifndef ADDEDITEXTERNALAPPWINDOW_H
#define ADDEDITEXTERNALAPPWINDOW_H

#include <QDialog>

namespace Ui {
	class AddEditExternalAppWindow;
	}

class AddEditExternalAppWindow : public QDialog
	{
		Q_OBJECT

	public:
		explicit AddEditExternalAppWindow(QWidget *parent = 0);
        void edit(int id, QString name, QString command, bool useInternalWindow, bool decode);
		~AddEditExternalAppWindow();

	private slots:
		void on_cancelButton_clicked();

		void on_internalWindowCheckBox_toggled(bool checked);
		void on_applyButton_clicked();

	signals:
        void append(QString name, QString command, bool useInternalWindow, bool decode);
        void update(int id, QString name, QString command, bool useInternalWindow, bool decode);
	private:
		Ui::AddEditExternalAppWindow *ui;
        int id;
	};

#endif // ADDEDITEXTERNALAPPWINDOW_H
