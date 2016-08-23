#include "ExportWindow.h"
#include "ui_ExportWindow.h"
#include <QFileDialog>

ExportWindow::ExportWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportWindow)
{
    ui->setupUi(this);
}

ExportWindow::~ExportWindow()
{
    delete ui;
}

void ExportWindow::on_buttonCancel_clicked()
{
    this->close();
}

void ExportWindow::on_buttonFileName_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Comma-Separated Values (*.csv)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList names;
    if(dialog.exec())
        {
        names = dialog.selectedFiles();
        this->ui->editFileName->setText(names.first());
        }

}

void ExportWindow::on_buttonExport_clicked()
{
emit exportAllToCSV(this->ui->editFileName->text(),
                    this->ui->checkId->isChecked(),
                    this->ui->checkIp->isChecked(),
                    this->ui->checkMask->isChecked(),
                    this->ui->checkHostName->isChecked(),
                    this->ui->checkMacAddress->isChecked(),
                    this->ui->checkUserName->isChecked(),
                    this->ui->checkDomain->isChecked(),
                    this->ui->checkLocation->isChecked(),
                    this->ui->checkDhcpReservation->isChecked(),
                    this->ui->checkDescription->isChecked(),
                    this->ui->checkHeader->isChecked(),
                    this->ui->checkNumber->isChecked(),
                    this->ui->comboSeparator->currentText());
    this->close();
}
