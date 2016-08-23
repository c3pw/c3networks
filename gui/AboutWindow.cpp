#include "AboutWindow.h"
#include "ui_AboutWindow.h"

#include <QDate>
#include <QTime>

#include <QDebug>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    QDate d = QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    this->ui->labelCompilationDate->setText(d.toString()+ ", " + __TIME__);
    this->ui->labelVersion->setText(QApplication::applicationVersion());
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_buttonClose_clicked()
{
    this->close();
}
