#include "AddEditExternalAppWindow.h"
#include "ui_AddEditExternalAppWindow.h"
#include <QDebug>

AddEditExternalAppWindow::AddEditExternalAppWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddEditExternalAppWindow)
	{
    this->id=-1;
	ui->setupUi(this);
	}

void AddEditExternalAppWindow::edit(int id, QString name, QString command,  bool useInternalWindow, bool decode)
	{
	this->id=id;
	this->ui->nameText->setText(name);
    this->ui->commandText->setPlainText(command);
	this->ui->internalWindowCheckBox->setChecked(useInternalWindow);
	this->ui->decodeCheckBox->setChecked(decode);
	this->setWindowTitle(tr("Edit external application"));
	this->show();
	}

AddEditExternalAppWindow::~AddEditExternalAppWindow()
	{
	delete ui;
	}

void AddEditExternalAppWindow::on_cancelButton_clicked()
	{
	this->close();
	}

void AddEditExternalAppWindow::on_internalWindowCheckBox_toggled(bool checked)
	{
	this->ui->decodeCheckBox->setEnabled(checked);
	if(!checked){this->ui->decodeCheckBox->setChecked(false);}
	}

void AddEditExternalAppWindow::on_applyButton_clicked()
	{


	if(!this->ui->nameText->text().isEmpty())
		{
        qDebug()<<"ID<0: "<<(this->id<0);
        if(this->id<0)
			{
            qDebug()<<"Emiting append";
            emit append(this->ui->nameText->text(),this->ui->commandText->toPlainText(),this->ui->internalWindowCheckBox->isChecked(), this->ui->decodeCheckBox->isChecked());
			}
		else
			{
            qDebug()<<"Emiting update";
            emit update(this->id,this->ui->nameText->text(),this->ui->commandText->toPlainText(),this->ui->internalWindowCheckBox->isChecked(), this->ui->decodeCheckBox->isChecked());
			}
			this->close();

		}
	}
