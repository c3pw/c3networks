#include "AddEditIfWindow.h"
#include "ui_AddEditIfWindow.h"

#include <QHostAddress>
#include <QSqlQuery>
#include <QHostAddress>

#include "../../database/IfDbTable.h"

AddEditIfWindow::AddEditIfWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddEditIfWindow)
	{
	id=0;
	ui->setupUi(this);

	quint32 number = 0;
	for(int i =31; i>0;i--)
		{
		number|=1<<i;
		masks.append(number);
		}

	nameCompleter = new QCompleter(IfDbTable::getHostNameSet(),this);
	this->ui->edit_name->setCompleter(nameCompleter);

	userNameCompleter =  new QCompleter(IfDbTable::getUserNameSet(),this);
	this->ui->edit_user->setCompleter(userNameCompleter);

	locationCompleter = new QCompleter(IfDbTable::getLocationSet(),this);
	this->ui->edit_location->setCompleter(locationCompleter);

	domainCompleter = new QCompleter(IfDbTable::getDomainSet(),this);
	this->ui->edit_domain->setCompleter(domainCompleter);

	maskCompleter = new QCompleter(IfDbTable::getMaskSet(),this);
	this->ui->edit_mask->setCompleter(maskCompleter);

	this->ui->edit_ip->setValidator(&ipValidator);
	this->ui->edit_mask->setValidator(&netMAskValidator);
	this->ui->edit_mac->setValidator(&macValidator);

	this->ui->comboGroup->setModel(&model);
	model.setComboMode(true);
	model.reloadData();
	}

AddEditIfWindow::~AddEditIfWindow()
	{
	delete ui;
	delete nameCompleter;
	delete userNameCompleter;
	delete locationCompleter;
	delete domainCompleter;
	delete maskCompleter;
	}

void AddEditIfWindow::addInterface()
	{
	this->show();
	}

void AddEditIfWindow::updateInterface(int id)
	{
	this->id=id;
	QSqlQuery query("select * from hosts where id=:id");
	query.bindValue(0,id);
	if(query.exec() && query.next())
		{
		this->ui->edit_ip->setText(QHostAddress(query.value("ipAddress").toUInt()).toString());
		this->ui->edit_mask->setText(QHostAddress(query.value("mask").toUInt()).toString());
		this->ui->edit_mac->setText(query.value("mac").toString());
		this->ui->check_inUse->setChecked(query.value("inUse").toInt()==1);
		this->ui->edit_name->setText(query.value("name").toString());
		this->ui->edit_user->setText(query.value("userName").toString());
		this->ui->edit_domain->setText(query.value("domain").toString());
		this->ui->edit_description->setPlainText(query.value("description").toString());
		this->ui->edit_location->setText(query.value("location").toString());
		this->ui->comboGroup->setCurrentIndex(this->model.idRow(query.value("groupId").toInt()));
		this->ui->check_dhcpReservation->setChecked(query.value("dhcpReservation").toInt()!=0);
		this->show();
		}
	}

void AddEditIfWindow::on_button_cancel_clicked()
	{
	this->close();
	}

void AddEditIfWindow::on_button_apply_clicked()
	{
	this->ui->edit_ip->setStyleSheet("");
	this->ui->edit_mask->setStyleSheet("");

	quint32 ip = QHostAddress(this->ui->edit_ip->text()).toIPv4Address();
	quint32 mask = QHostAddress(this->ui->edit_mask->text()).toIPv4Address();
	quint32 network = ip&mask;
	quint32 broadcast = network | ~mask;
	QString mac = ui->edit_mac->text().replace(':',"");

	if(ip == 0)
		{
		this->ui->edit_ip->setStyleSheet("background-color: rgb(255, 123, 123);");
		return;
		}

	if(!masks.contains(mask))
		{
		this->ui->edit_mask->setStyleSheet("background-color: rgb(255, 123, 123);");
		return;
		}

	if(network == ip || broadcast == ip)
		{
		this->ui->edit_ip->setStyleSheet("background-color: rgb(255, 123, 123);");
		return;
		}

	if(mac.size()!=0 && mac.size()!=12)
		{
		this->ui->edit_mac->setStyleSheet("background-color: rgb(255, 123, 123);");
		return;
		}

	bool inUse = this->ui->check_inUse->isChecked();
	QString name = this->ui->edit_name->text();
	QString user = this->ui->edit_user->text();
	QString domain = this->ui->edit_domain->text();
	QString description = this->ui->edit_description->toPlainText();
	QString location = this->ui->edit_location->text();
	bool dhcp = this->ui->check_dhcpReservation->isChecked();

	int group=this->ui->comboGroup->currentData().toInt();

	if(id == 0)
		{
		emit addInterface(ip, mask, name, mac, user, domain, description, inUse,group,location,dhcp);
		this->close();
		}
	else
		{
		emit updateInterface(id, ip, mask, name, mac, user, domain, description, inUse,group,location,dhcp);
		this->close();
		}
	}
