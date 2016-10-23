#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"
#include "global/LocalSettings.h"


SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsWindow)
    {
    ui->setupUi(this);

	this->filterHilightColorDialog.setOption(QColorDialog::ShowAlphaChannel);
	this->filterHilightColor_changed(QColor(0, 255, 0, 50));
	this->filterHilightColorDialog.setCurrentColor(QColor(0, 255, 0, 50));

	connect(&(this->filterHilightColorDialog),SIGNAL(colorSelected(QColor)),this,SLOT(filterHilightColor_changed(QColor)));

	loadSettings();

    }

SettingsWindow::~SettingsWindow()
    {
    delete ui;
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
	s.setValue("cp852conversion",this->ui->cp852conversion_YES->isChecked());

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


	if(s.value("cp852conversion").toBool())
		{
		this->ui->cp852conversion_YES->setChecked(true);
		}
	else
		{
		this->ui->cp852conversion_NO->setChecked(true);
		}
	}
