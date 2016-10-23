#include "GropusManagerWindow.h"
#include "ui_GropusManagerWindow.h"

#include "AddEditGroupWindow.h"
#include "../../database/GroupItem.h"

#include <QMessageBox>

GropusManagerWindow::GropusManagerWindow(QWidget *parent) : QDialog(parent), ui(new Ui::GropusManagerWindow)
	{
	setAttribute(Qt::WA_DeleteOnClose);
	ui->setupUi(this);
	this->model = new GrTableModel();
	this->ui->listView->setModel(this->model);
	this->model->reloadData();
	this->ui->listView->setCurrentIndex(this->ui->listView->rootIndex());
	connect(this,SIGNAL(deleteGroup(int)),this->model,SLOT(deleteGroup(int)));
	}

GropusManagerWindow::~GropusManagerWindow()
	{
	delete ui;
	delete this->model;
	}

void GropusManagerWindow::on_buttonClose_clicked()
	{
	this->close();
	}

void GropusManagerWindow::on_buttonAddGroup_clicked()
	{
	AddEditGroupWindow * form = new AddEditGroupWindow(this);
	connect(form,SIGNAL(addGroup(QString,QString)),this->model,SLOT(addGroup(QString,QString)));
	form->show();
	}

void GropusManagerWindow::on_buttonEditGroup_clicked()
	{
	if(this->ui->listView->currentIndex().row()>=0)
		{
		AddEditGroupWindow * form = new AddEditGroupWindow(this);
		connect(form,SIGNAL(updateGroup(int,QString,QString)),this->model,SLOT(updateGroup(int,QString,QString)));
		form->editShow(((GroupItem*)this->ui->listView->currentIndex().internalPointer())->getId());
		}
	}

void GropusManagerWindow::on_buttonRemoveGroup_clicked()
	{
	if(this->ui->listView->currentIndex().row() >= 0)
		{
		QMessageBox box;
		box.setText(tr("Are you sure you want to delete group?"));
		box.setIcon(QMessageBox::Critical);
		box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		box.setDefaultButton(QMessageBox::No);
		if(box.exec() == QMessageBox::Yes)
			{
			emit this->deleteGroup(((GroupItem*)this->ui->listView->currentIndex().internalPointer())->getId());
			}
		}
	}
