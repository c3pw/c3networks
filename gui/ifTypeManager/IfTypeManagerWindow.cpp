#include "IfTypeManagerWindow.h"
#include "ui_IfTypeManagerWindow.h"

#include "AddEditIfTypeWindow.h"
#include "../../database/InterfaceTypeItem.h"
#include <QMessageBox>

IfTypeManagerWindow::IfTypeManagerWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IfTypeManagerWindow)
	{
	ui->setupUi(this);
	this->model = new IfTypeTableModel();
	this->ui->listView->setModel(this->model);
	model->loadData();
	connect(this,SIGNAL(deleteIfType(int)),model,SLOT(remove(int)));
	}

IfTypeManagerWindow::~IfTypeManagerWindow()
	{
	delete ui;
	delete model;
	}

void IfTypeManagerWindow::on_buttonClose_clicked()
{
	this->close();
}

void IfTypeManagerWindow::on_buttonAdd_clicked()
{
	AddEditIfTypeWindow * form = new AddEditIfTypeWindow(this);
	form->setAttribute(Qt::WA_DeleteOnClose);
	connect(form,SIGNAL(addIfType(QString,QPixmap)),this->model,SLOT(insert(QString,QPixmap)));
	form->show();
}

void IfTypeManagerWindow::on_buttonEdit_clicked()
{

	if(this->ui->listView->currentIndex().row()>=0)
		{
		AddEditIfTypeWindow * form = new AddEditIfTypeWindow(this);

		InterfaceTypeItem* item = this->model->getItem(this->ui->listView->currentIndex().row());
		if(item!=NULL)
		{
		form->setAttribute(Qt::WA_DeleteOnClose);
		connect(form,SIGNAL(updateIfType(int,QString,QPixmap)),this->model,SLOT(update(int,QString,QPixmap)));
		form->editShow(item->getId());
			}
		}
}

void IfTypeManagerWindow::on_buttonRemove_clicked()
{
	if(this->ui->listView->currentIndex().row() >= 0)
		{
		QMessageBox box;
		box.setText(tr("Are you sure you want to delete item?"));
		box.setIcon(QMessageBox::Critical);
		box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		box.setDefaultButton(QMessageBox::No);
		if(box.exec() == QMessageBox::Yes)
			{
			InterfaceTypeItem* item = this->model->getItem(this->ui->listView->currentIndex().row());
			if(item!=NULL)
				{
				emit this->deleteIfType(item->getId());
				}

			}
		}

}
