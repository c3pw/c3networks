#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "SettingsWindow.h"
#include "AboutWindow.h"
#include "interfaces/AddEditIfWindow.h"
#include "interfaces/ChangeGroupWindow.h"
#include "interfaces/AddRangeWindow.h"
#include "ExportWindow.h"

#include "../database/InterfaceItem.h"
#include "groupsManager/GropusManagerWindow.h"



#include <QMessageBox>
#include <QPointer>

#include <QDebug>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
    {
    ui->setupUi(this);
    this->ui->menuBar->insertAction(this->ui->menuBar->actions().first(),this->ui->actionSettings);

    this->tableModel = new IfTabeModel();
    connect(&ifDbTable,SIGNAL(prepareToModelReset()),this,SLOT(prepareToModelReset()));
    connect(this,SIGNAL(deleteInterfaces(QList<int>)),&ifDbTable,SLOT(deleteInterfaces(QList<int>)));

    this->tableProxy = new IfTableSortProxy();

    this->tableProxy->setSourceModel(this->tableModel);
    this->tableProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->ui->ifTable->setModel(tableProxy);
    this->ui->ifTable->sortByColumn(0,Qt::AscendingOrder);
    this->tableModel->loadData();

    rightButtonMenu.insertAction(0,this->ui->actionChangeGroup);
    this->ui->ifTable->setContextMenuPolicy(Qt::CustomContextMenu);
    this->ui->ifTable->resizeColumnToContents(2);
	this->ui->ifTableFilterBox->insertItem(0,tr("Ip Address"),IfTabeModel::IP);
	this->ui->ifTableFilterBox->insertItem(1,tr("Host Name"),IfTabeModel::NAME);
	this->ui->ifTableFilterBox->insertItem(2,tr("MAC Address"),IfTabeModel::MAC);
	this->ui->ifTableFilterBox->insertItem(3,tr("User Name"),IfTabeModel::USERNAME);
	this->ui->ifTableFilterBox->insertItem(4,tr("Location"),IfTabeModel::LOCATION);
	this->ui->ifTableFilterBox->insertItem(5,tr("Domain"),IfTabeModel::HOSTDOMAIN);
	this->ui->ifTableFilterBox->insertItem(6,tr("Description"),IfTabeModel::DESCRIPTION);
    }

MainWindow::~MainWindow()
    {
    delete ui;
    }

void MainWindow::on_ifTableFilterEdit_textChanged(const QString &arg1)
    {
    //this->tableProxy->setFilterFixedString(".*"+arg1+".*");
    this->tableProxy->setFilterRegExp("^.*"+arg1+".*$");
	this->ui->ifTable->reset();
    }

void MainWindow::on_buttonRefresh_clicked()
    {
    this->tableModel->loadData();
    }

void MainWindow::on_pushButton_clicked()
    {
    AddEditIfWindow *w = new AddEditIfWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    connect(w,SIGNAL(addInterface(quint32,quint32,QString,QString,QString,QString,QString,bool,int,QString,bool)),
            &ifDbTable,SLOT(addInterface(quint32,quint32,QString,QString,QString,QString,QString,bool,int,QString,bool)));
    w->addInterface();
    }

void MainWindow::on_buttonEditHost_clicked()
    {
    QList<QModelIndex> list = this->ui->ifTable->selectionModel()->selectedRows();
    qDebug()<<list;

    if(list.count()==1)
        {
        QPointer<InterfaceItem> item = tableModel->getInterfaceItem(tableProxy->mapToSource(list.first()));


        if(!item.isNull())
            {
            AddEditIfWindow *w = new AddEditIfWindow(this);
            w->setAttribute(Qt::WA_DeleteOnClose);
            connect(w,SIGNAL(updateInterface(int,quint32,quint32,QString,QString,QString,QString,QString,bool,int,QString,bool)),
                    &ifDbTable,SLOT(updateInterface(int,quint32,quint32,QString,QString,QString,QString,QString,bool,int,QString,bool)));
            w->updateInterface(item->getId());
            }
        }
    }

void MainWindow::on_buttonGroupsManager_clicked()
    {
    GropusManagerWindow *w = new GropusManagerWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    }

void MainWindow::on_ifTable_doubleClicked(const QModelIndex &index)
    {
    Q_UNUSED(index)
    on_buttonEditHost_clicked();
    }

void MainWindow::prepareToModelReset()
    {
    this->tableModel->loadData();
    }

void MainWindow::on_actionAbout_Application_triggered()
    {
    AboutWindow *w = new AboutWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    }

void MainWindow::on_actionAbout_QT_triggered()
    {
    QApplication::aboutQt();
    }

void MainWindow::on_actionSettings_triggered()
    {
    SettingsWindow *w = new SettingsWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
    }

void MainWindow::on_buttonRemoveHost_clicked()
    {
    QList<QModelIndex> list = this->ui->ifTable->selectionModel()->selectedRows();
    QList<int> idx;

    if(list.count()>0)
        {
        QMessageBox box;
        box.setWindowTitle(tr("Delete"));
        box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        box.setDefaultButton(QMessageBox::No);
        box.setButtonText(QMessageBox::No,tr("No"));
        box.setButtonText(QMessageBox::Yes,tr("Yes"));
        box.setIcon(QMessageBox::Critical);
        box.setText(tr("Would you like to delete selected records?"));
        if(box.exec() == QMessageBox::Yes)
            {

            for(int i=0; i< list.count();i++)
                {
                QPointer<InterfaceItem> item = tableModel->getInterfaceItem(tableProxy->mapToSource(list.at(i)));
                if(!item.isNull())
                    {
                    idx.append(item->getId());
                    }
                }
            emit deleteInterfaces(idx);
            }
        }
    }

void MainWindow::on_ifTable_customContextMenuRequested(const QPoint &pos)
    {
    this->rightButtonMenu.popup(this->ui->ifTable->viewport()->mapToGlobal(pos));
    }

void MainWindow::on_actionChangeGroup_triggered()
    {
    QList<QModelIndex> list = this->ui->ifTable->selectionModel()->selectedRows();
    QList<int> idx;

    if(list.count()>0)
        {
        for(int i=0; i< list.count();i++)
            {
            QPointer<InterfaceItem> item = tableModel->getInterfaceItem(tableProxy->mapToSource(list.at(i)));
            if(!item.isNull())
                {
                idx.append(item->getId());
                }
            }

        ChangeGroupWindow *w = new ChangeGroupWindow(this);
        w->setAttribute(Qt::WA_DeleteOnClose);
        connect(w,SIGNAL(changeGroup(QList<int>,int)),&ifDbTable,SLOT(changeGroup(QList<int>,int)));
        w->setIdxList(idx);
        w->show();
        }
    }

void MainWindow::on_pushAddRange_clicked()
    {
    AddRangeWindow *w = new AddRangeWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    connect(w,SIGNAL(addInterfaces(quint32,quint32,quint32,int)),&ifDbTable,SLOT(addInterfaces(quint32,quint32,quint32,int)));
    w->show();
    }

void MainWindow::on_actionExport_triggered()
    {
    ExportWindow *w = new ExportWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    connect(w,SIGNAL(exportAllToCSV(QString,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,QString)),
            &ifDbTable,SLOT(exportAllToCSV(QString,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,QString)));
    w->show();
    }

void MainWindow::on_ifTableFilterModeButton_toggled(bool checked)
{
	this->tableProxy->setAllColumnsFilter(checked);
	this->ui->ifTableFilterBox->setEnabled(!checked);
	this->tableProxy->setFilterRegExp("^.*"+this->ui->ifTableFilterEdit->text()+".*$");
	this->ui->ifTable->reset();
}

void MainWindow::on_ifTableFilterBox_activated(int index)
{
Q_UNUSED(index)
this->tableProxy->setFilterKeyColumn(this->ui->ifTableFilterBox->currentData().toInt());
this->tableProxy->setFilterRegExp("^.*"+this->ui->ifTableFilterEdit->text()+".*$");
}
