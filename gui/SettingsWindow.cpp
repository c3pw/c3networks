#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"
#include "global/LocalSettings.h"
#include "externalApps/AddEditExternalAppWindow.h"
#include <QFileDialog>
#include <QDebug>


SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsWindow)
    {
    ui->setupUi(this);

	this->filterHilightColorDialog.setOption(QColorDialog::ShowAlphaChannel);
	this->filterHilightColor_changed(QColor(0, 255, 0, 50));
	this->filterHilightColorDialog.setCurrentColor(QColor(0, 255, 0, 50));

	connect(&(this->filterHilightColorDialog),SIGNAL(colorSelected(QColor)),this,SLOT(filterHilightColor_changed(QColor)));

	this->externalAppModel = new ExternalAppModel();
	this->ui->externalAppTable->setModel(this->externalAppModel);

	loadSettings();

    }

SettingsWindow::~SettingsWindow()
    {
    delete ui;
	delete this->externalAppModel;
    }

void SettingsWindow::on_buttonCancel_clicked()
    {
    this->close();
    }


void SettingsWindow::on_buttonSave_clicked()
	{
	LocalSettings s;
	s.setValue("rememberFilterMode",this->ui->rememberFilterMode_YES->isChecked());
	s.setValue("filterHilightColor",this->ui->filterHilightColor->text());
	this->externalAppModel->saveData();
    emit settingsChanged();
	this->close();
	}

void SettingsWindow::on_filterHilightColorButton_clicked()
	{
	this->filterHilightColorDialog.exec();
	}

void SettingsWindow::filterHilightColor_changed(QColor c)
	{
	this->ui->filterHilightColor->setStyleSheet("background-color: "+c.name(QColor::HexArgb)+";");
	this->ui->filterHilightColor->setText(c.name(QColor::HexArgb));
	}

void SettingsWindow::loadSettings()
	{
	LocalSettings s;

	if(s.value("rememberFilterMode").toBool())
		{
		this->ui->rememberFilterMode_YES->setChecked(true);
		}
	else
		{
		this->ui->rememberFilterMode_NO->setChecked(true);
		}


	QString str;
	str = s.value("filterHilightColor").toString();
	if(!str.isEmpty())
		{
		this->filterHilightColor_changed(QColor(str));
		this->filterHilightColorDialog.setCurrentColor(QColor(str));
		}

	this->externalAppModel->loadData();
	}

void SettingsWindow::on_addExtarnalAppButton_clicked()
	{
	AddEditExternalAppWindow *window = new AddEditExternalAppWindow(this);
	window->setAttribute(Qt::WA_DeleteOnClose);
    connect(window,SIGNAL(append(QString,QString,bool,bool)),this->externalAppModel,SLOT(append(QString,QString,bool,bool)));
	window->show();
	}


void SettingsWindow::on_removeExtarnalAppButton_clicked()
	{
	if(this->ui->externalAppTable->selectionModel()->selectedRows().count()==1)
		{
		this->externalAppModel->remove(this->ui->externalAppTable->selectionModel()->selectedRows().first().row());
		}
	}

void SettingsWindow::on_editExtarnalAppButton_clicked()
	{
	if(this->ui->externalAppTable->selectionModel()->selectedRows().count()==1)
		{
		int i =  this->ui->externalAppTable->selectionModel()->selectedRows().first().row();
		ExternalAppItem item= this->externalAppModel->getItem(this->ui->externalAppTable->selectionModel()->selectedRows().first());
		AddEditExternalAppWindow *window = new AddEditExternalAppWindow(this);
		window->setAttribute(Qt::WA_DeleteOnClose);
        connect(window,SIGNAL(update(int,QString,QString,bool,bool)),this->externalAppModel,SLOT(update(int,QString,QString,bool,bool)));
        window->edit(i,item.getName(),item.getCommand(),item.getUseInternalWindow(),item.getDecodeFromCp852PL());
		}
	}
