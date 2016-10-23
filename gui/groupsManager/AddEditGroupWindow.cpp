#include "AddEditGroupWindow.h"
#include "ui_AddEditGroupWindow.h"

#include <QColorDialog>
#include <QSqlQuery>
#include <QSqlError>

AddEditGroupWindow::AddEditGroupWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddEditGroupWindow)
	{
	setAttribute(Qt::WA_DeleteOnClose);
	ui->setupUi(this);
	id=0;
	}

AddEditGroupWindow::~AddEditGroupWindow()
	{
	delete ui;
	}

void AddEditGroupWindow::editShow(int id)
	{
	this->id = id;
	QSqlQuery query("select * from groups where id=:id;");
	query.bindValue(0,id);
	if(query.exec())
		{
		query.next();
		this->ui->editName->setText(query.value("name").toString());
		this->ui->editColor->setText(query.value("color").toString());
		this->ui->frameColor->setStyleSheet("background-color:"+(query.value("color").toString())+";");
		this->show();
		}
	}

void AddEditGroupWindow::on_buttonColorDialog_clicked()
	{
	QColorDialog *d = new QColorDialog(this);
	d->setCurrentColor(QColor(this->ui->editColor->text()));
	d->exec();
	QColor c = d->selectedColor();
	if(c.isValid())
		{
		this->ui->editColor->setText(c.name());
		this->ui->frameColor->setStyleSheet("background-color:"+c.name()+";");
		}
	}

void AddEditGroupWindow::on_buttonCancel_clicked()
	{
	this->close();
	}

void AddEditGroupWindow::on_buttonApply_clicked()
	{
	if(!this->ui->editName->text().isEmpty())
		{
		if(id==0)
			{
			emit addGroup(this->ui->editName->text(),this->ui->editColor->text());

			}
		else
			{
			emit updateGroup(id,this->ui->editName->text(),this->ui->editColor->text());
			}
		this->close();
		}
	}
