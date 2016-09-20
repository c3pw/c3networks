#include "SelectDbWindow.h"
#include "ui_SelectDbWindow.h"
#include "MainWindow.h"

#include <QMessageBox>
#include "selectDb/AddEditDbFileWindow.h"

#include <QDebug>

SelectDbWindow::SelectDbWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SelectDbWindow)
	{
	ui->setupUi(this);
	model.loadData();
	this->ui->listDb->setModel(&model);
	this->ui->listDb->setItemDelegateForColumn(0,&htmlHelper);
	QModelIndex first = model.index(0,0);
	if(first.isValid())
		{
		this->ui->listDb->setCurrentIndex(first);
		this->on_listDb_clicked(first);
		}
	}

SelectDbWindow::~SelectDbWindow()
	{
	delete ui;
	}

void SelectDbWindow::on_buttonClose_clicked()
	{
	this->close();
	}

void SelectDbWindow::on_listDb_clicked(const QModelIndex &index)
	{
	Q_UNUSED(index);
	this->ui->buttonConfirm->setEnabled(true);
	this->ui->buttonEditItem->setEnabled(true);
	this->ui->buttonRemoveItem->setEnabled(true);
	}

void SelectDbWindow::on_buttonConfirm_clicked()
	{
	DbFileItem item = model.getDbFileItem(this->ui->listDb->currentIndex());
	if(item.analizeFile())
		{
		if(item.openDbConnection())
			{
			MainWindow *w = new MainWindow();
			w->setAttribute(Qt::WA_DeleteOnClose);
			w->show();
			this->close();
			}
		else
			{
			QMessageBox box;
			box.setWindowTitle(tr("Error"));
			box.setText(tr("Can't open file with database."));
			box.setIcon(QMessageBox::Critical);
			box.exec();
			}
		}
	}

void SelectDbWindow::on_listDb_activated(const QModelIndex &index)
	{
	Q_UNUSED(index);
	on_buttonConfirm_clicked();
	}

void SelectDbWindow::on_buttonAddItem_clicked()
	{
	AddEditDbFileWindow *w =new AddEditDbFileWindow(this);
	w->setAttribute(Qt::WA_DeleteOnClose);
	connect(w,SIGNAL(addItem(QString,QString,QString)),&model,SLOT(addItem(QString,QString,QString)));
	w->show();
	}

void SelectDbWindow::on_buttonEditItem_clicked()
	{
	if(this->ui->listDb->currentIndex().row()!=-1)
		{
		DbFileItem item = model.getDbFileItem(this->ui->listDb->currentIndex());
		AddEditDbFileWindow *w =new AddEditDbFileWindow(this);
		w->setAttribute(Qt::WA_DeleteOnClose);
		w->setData(this->ui->listDb->currentIndex().row(),item.getName(),item.getFileName(),item.getDescription());
		connect(w,SIGNAL(updateItem(int,QString,QString,QString)),&model,SLOT(updateItem(int,QString,QString,QString)));
		w->show();
		}
	}

void SelectDbWindow::on_buttonRemoveItem_clicked()
	{
	if(this->ui->listDb->currentIndex().row()!=-1)
		{
		QMessageBox box;
		box.setWindowTitle(tr("Remove"));
		box.setText(tr("Would you like to remove this entry?"));
		box.setIcon(QMessageBox::Question);
		box.setStandardButtons(QMessageBox::No|QMessageBox::Yes);
		box.setDefaultButton(QMessageBox::No);
		if(box.exec()==QMessageBox::Yes)
			{
			model.removeItem(this->ui->listDb->currentIndex().row());
			}
		}
	}
