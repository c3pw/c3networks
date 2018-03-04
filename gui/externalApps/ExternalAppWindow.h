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
        void executeApp(QString app,bool convert);
		~ExternalAppWindow();
	private slots:
		void onStdoutAvailable();
		void onFinished(int,QProcess::ExitStatus);
	private:
		Ui::ExternalAppWindow *ui;
		QProcess *process;
		QString ap;
        bool convert;
	};

#endif // EXTERNALAPPWINDOW_H
