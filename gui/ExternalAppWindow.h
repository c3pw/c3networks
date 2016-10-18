#ifndef EXTERNALAPPWINDOW_H
#define EXTERNALAPPWINDOW_H

#include <QDialog>
#include <QProcess>

namespace Ui {
	class ExternalAppWindow;
	}

class ExternalAppWindow : public QDialog
	{
		Q_OBJECT

	public:
		explicit ExternalAppWindow(QWidget *parent = 0);
		void executeApp(QString app,QStringList params);
		~ExternalAppWindow();
	private slots:
		void onStdoutAvailable();
		void onFinished(int,QProcess::ExitStatus);
	private:
		Ui::ExternalAppWindow *ui;
		QProcess *process;
	};

#endif // EXTERNALAPPWINDOW_H
