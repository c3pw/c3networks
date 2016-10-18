#include "ExternalAppWindow.h"
#include "ui_ExternalAppWindow.h"

#include <QDebug>
#include <QScrollBar>
#include "textCodecs/CP852PLCodec.h"

ExternalAppWindow::ExternalAppWindow(QWidget *parent) : QDialog(parent), ui(new Ui::ExternalAppWindow)
	{
	this->process = new QProcess();
	connect( process, SIGNAL(readyReadStandardOutput()), SLOT(onStdoutAvailable()) );
	connect( process, SIGNAL(finished(int,QProcess::ExitStatus)), SLOT(onFinished(int,QProcess::ExitStatus)) );
	ui->setupUi(this);
	}

void ExternalAppWindow::executeApp(QString app, QStringList params)
	{
	this->show();
	QString p;
	for(int i=0;i<params.count();i++)
		{
		p.append(" ").append(params.at(i));
		}
	this->ui->plainTextEdit->appendPlainText("EXECUTE: "+app+p+"\n----------------------------------\n\n");
	this->process->start(app,params);



	}

ExternalAppWindow::~ExternalAppWindow()
	{
	delete this->process;
	delete ui;
	}

void ExternalAppWindow::onStdoutAvailable()
	{
	QString str = CP852PLCodec::fromCP852PL(this->process->readAll());
	this->ui->plainTextEdit->insertPlainText(str);


	QScrollBar *sb = this->ui->plainTextEdit->verticalScrollBar();
	sb->setValue(sb->maximum());
	}

void ExternalAppWindow::onFinished(int, QProcess::ExitStatus)
	{
	this->setWindowTitle("Finished");
	QFile f("d:/test_stream.txt");
	f.open(QIODevice::WriteOnly);
	QDataStream s(&f);
	s<<this->ui->plainTextEdit->toPlainText();
	f.close();
	}
