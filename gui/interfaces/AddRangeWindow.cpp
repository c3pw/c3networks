#include "AddRangeWindow.h"
#include "ui_AddRangeWindow.h"

#include <QHostAddress>
#include <QDebug>

AddRangeWindow::AddRangeWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddRangeWindow)
    {
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);


    quint32 number = 0;
    for(int i =31; i>0;i--)
        {
        number|=1<<i;
        masks.append(number);
        }

    this->model = new GrTableModel();
    model->setComboMode(true);
    this->ui->comboGroup->setModel(this->model);
    this->model->reloadData();
    this->ui->comboGroup->setCurrentIndex(this->model->idRow(0));

    this->ui->edit_network->setValidator(&ipValidator);
    this->ui->edit_mask->setValidator(&netMaskValidator);
    this->ui->edit_from->setValidator(&ipValidator);
    this->ui->edit_to->setValidator(&ipValidator);

    maskCompleter = new QCompleter(IfDbTable::getMaskSet(),this);
    this->ui->edit_mask->setCompleter(maskCompleter);
    }

AddRangeWindow::~AddRangeWindow()
    {
    delete ui;
    delete model;
    }

void AddRangeWindow::on_button_apply_clicked()
    {

    this->ui->edit_mask->setStyleSheet("");
    this->ui->edit_network->setStyleSheet("");
    this->ui->edit_from->setStyleSheet("");
    this->ui->edit_to->setStyleSheet("");


    network = QHostAddress(this->ui->edit_network->text()).toIPv4Address();
    mask = QHostAddress(this->ui->edit_mask->text()).toIPv4Address();
    broadcast = network | ~mask;
    quint32 from = QHostAddress(ui->edit_from->text()).toIPv4Address();
    quint32 to = QHostAddress(ui->edit_to->text()).toIPv4Address();

    /*
    qDebug()<<"mask:     \t"<<QHostAddress(mask).toString();
    qDebug()<<"network:  \t"<<QHostAddress(network).toString();
    qDebug()<<"broadcast:\t"<<QHostAddress(broadcast).toString();
    qDebug()<<"from:     \t"<<QHostAddress(from).toString();
    qDebug()<<"to:       \t"<<QHostAddress(to).toString();
    */

    if(!masks.contains(mask))
        {
        this->ui->edit_mask->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
        }
    if((network&mask) != network)
        {
        this->ui->edit_network->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
        }
    if(from<=network || from>=broadcast)
        {
        this->ui->edit_from->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
        }
    if(to<=network || to>=broadcast)
        {
        this->ui->edit_to->setStyleSheet("background-color: rgb(255, 123, 123);");
        return;
        }
    if(from>to)
        {
        this->ui->edit_from->setStyleSheet("background-color: rgb(255, 123, 123);");
        this->ui->edit_to->setStyleSheet("background-color: rgb(255, 123, 123);");
        }

    int group=this->ui->comboGroup->currentData().toInt();

    emit addInterfaces(from,to,mask,group);
    this->close();
    }

void AddRangeWindow::on_button_cancel_clicked()
    {
    this->close();
    }
