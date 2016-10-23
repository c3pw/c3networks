#include "DatabaseUpdateWindow.h"
#include "ui_DatabaseUpdateWindow.h"

#include <QMessageBox>

DatabaseUpdateWindow::DatabaseUpdateWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DatabaseUpdateWindow)
	{
	this->updater = new DatabaseUpdater;
	this->updater->moveToThread(&(this->thread));

	connect(this->updater,SIGNAL(setMaxValue(int)),this,SLOT(setMaxValue(int)),Qt::QueuedConnection);
	connect(this->updater,SIGNAL(setValue(int)),this,SLOT(setValue(int)),Qt::QueuedConnection);
	connect(this->updater,SIGNAL(finished()),this,SLOT(canBeClosed()),Qt::QueuedConnection);


	this->thread.start();

	ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);
	movie.setFileName(":/icons/progress.gif");
	this->ui->animationLabel->setMovie(&movie);
	this->movie.start();
	}

DatabaseUpdateWindow::~DatabaseUpdateWindow()
	{
	delete ui;
	this->thread.terminate();
	delete updater;
	}

void DatabaseUpdateWindow::update(DbFileItem& item)
	{
	this->show();
	this->updater->update(item);
	}

void DatabaseUpdateWindow::setMaxValue(int max)
	{
	this->ui->progressBar->setMaximum(max);
	}

void DatabaseUpdateWindow::setValue(int value)
	{
	this->ui->progressBar->setValue(value);
	this->ui->message->setText("Working");
	}

void DatabaseUpdateWindow::canBeClosed()
	{
	//this->setWindowFlags(this->windowFlags() & Qt::WindowCloseButtonHint);
	this->ui->closeButton->setEnabled(true);
	this->ui->message->setText("Finished");
	this->movie.stop();
	}

void DatabaseUpdateWindow::error(QString error)
	{
	QMessageBox box(this);
	box.setWindowTitle(tr("Error"));
	box.setText(error);
	box.setIcon(QMessageBox::Critical);
	box.exec();
	this->close();
	}

void DatabaseUpdateWindow::on_closeButton_clicked()
	{
	this->close();
	}
