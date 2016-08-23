#include "ChangeGroupWindow.h"
#include "ui_ChangeGroupWindow.h"

ChangeGroupWindow::ChangeGroupWindow(QWidget *parent) : QDialog(parent), ui(new Ui::ChangeGroupWindow)
    {
    ui->setupUi(this);
    model.setComboMode(true);
    model.reloadData();
    this->ui->comboGroup->setModel(&(this->model));
    }

ChangeGroupWindow::~ChangeGroupWindow()
    {
    delete ui;
    }

void ChangeGroupWindow::on_buttonCancel_clicked()
    {
    this->close();
    }

void ChangeGroupWindow::setIdxList(const QList<int> &value)
    {
    idx = value;
    }

void ChangeGroupWindow::on_buttonApply_clicked()
    {
    int group=this->ui->comboGroup->currentData().toInt();
    emit changeGroup(idx,group);
    this->close();
    }
