#ifndef ADDEDITHOSTFORM_H
#define ADDEDITHOSTFORM_H

#include <QDialog>
#include "../../models/GrTableModel.h"
#include "../validators/IPValidator.h"
#include "../validators/NetMaskValidator.h"
#include "../validators/MacValidator.h"

#include <QCompleter>

namespace Ui { class AddEditIfWindow; }

class AddEditIfWindow : public QDialog
	{
		Q_OBJECT
	public:
		explicit AddEditIfWindow(QWidget *parent = 0);
		~AddEditIfWindow();
		void addInterface();
		void updateInterface(int id);
	private slots:
		void on_button_cancel_clicked();
		void on_button_apply_clicked();
	private:
		Ui::AddEditIfWindow *ui;
		int id;
		QList<quint32> masks;
		GrTableModel model;
		IpValidator ipValidator;
		NetMaskValidator netMAskValidator;
		MacValidator macValidator;
		QCompleter *nameCompleter;
		QCompleter *userNameCompleter;
		QCompleter *locationCompleter;
		QCompleter *domainCompleter;
		QCompleter *maskCompleter;
	signals:
		void addInterface(quint32 ipAddress, quint32 mask,
						  QString name, QString mac, QString userName,
						  QString domain,QString description, bool inUse,
						  int groupId, QString location, bool dhcpReservation);
		void updateInterface(int id,quint32 ipAddress, quint32 mask,
							 QString name, QString mac, QString userName,
							 QString domain,QString description, bool inUse,
							 int groupId, QString location, bool dhcpReservation);
	};

#endif // ADDEDITHOSTFORM_H
