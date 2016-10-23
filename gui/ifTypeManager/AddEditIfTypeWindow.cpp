#include "AddEditIfTypeWindow.h"
#include "ui_AddEditIfTypeWindow.h"
#include <QSqlQuery>
#include <QFileDialog>
#include <QBuffer>
#include <QPixmap>

AddEditIfTypeWindow::AddEditIfTypeWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddEditIfTypeWindow)
	{
	ui->setupUi(this);
	this->id=0;
	}

AddEditIfTypeWindow::~AddEditIfTypeWindow()
	{
	delete ui;
	}

void AddEditIfTypeWindow::editShow(int id)
	{
	this->id = id;
	QSqlQuery query("select * from interfaces where id=:id;");
	query.bindValue(0,id);
	if(query.exec())
		{
		query.first();
		this->ui->editName->setText(query.value("name").toString());
		QPixmap p;
		p.loadFromData( query.value("icon").toByteArray());
		this->ui->labelIcon->setPixmap(p);
		}
	this->show();
	}

void AddEditIfTypeWindow::on_buttonClose_clicked()
	{
		this->close();
	}

void AddEditIfTypeWindow::on_toolButton_clicked()
	{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
	this->ui->labelIcon->setPixmap(QPixmap(fileName));
	}

void AddEditIfTypeWindow::on_buttonConfirm_clicked()
	{
	if(!this->ui->editName->text().trimmed().isEmpty())
		{
		QPixmap p = *(this->ui->labelIcon->pixmap());
		p.scaled(16,16);

		if(id==0)
			{
			emit this->addIfType(this->ui->editName->text().trimmed(),p);
			}
		else
			{
			emit this->updateIfType(this->id,this->ui->editName->text().trimmed(),p);
			}
		this->close();
		}
	}
