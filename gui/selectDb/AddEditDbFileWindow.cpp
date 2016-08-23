#include "AddEditDbFileWindow.h"
#include "ui_AddEditDbFileWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AddEditDbFileWindow::AddEditDbFileWindow(QWidget *parent): QDialog(parent), ui(new Ui::AddEditDbFileWindow)
    {
    ui->setupUi(this);
    this->id=-1;
    createMenu.addAction(this->ui->actionSelectDatabaseFile);
    createMenu.addAction(this->ui->actionCreateNewDatabaseFile);
    this->ui->buttonFile->setMenu(&createMenu);
    }

AddEditDbFileWindow::~AddEditDbFileWindow()
    {
    delete ui;
    }

void AddEditDbFileWindow::setData(int id, QString name, QString fileName, QString description)
    {
    this->id=id;
    this->ui->editName->setText(name);
    this->ui->editFileName->setText(fileName);
    this->ui->editDescription->setPlainText(description);
    }

void AddEditDbFileWindow::on_buttonCancel_clicked()
    {
    this->close();
    }

void AddEditDbFileWindow::on_buttonConfirm_clicked()
    {
    if(!this->ui->editName->text().isEmpty() && !this->ui->editFileName->text().isEmpty())
        {
        if(this->id==-1)
            {
            emit addItem(this->ui->editName->text(),this->ui->editFileName->text(),this->ui->editDescription->toPlainText());
            }
        else
            {
            emit updateItem(this->id,this->ui->editName->text(),this->ui->editFileName->text(),this->ui->editDescription->toPlainText());
            }
        this->close();
        }
    }

void AddEditDbFileWindow::on_actionSelectDatabaseFile_triggered()
    {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Database (*.sqlite)"));
    QStringList names;
    if(dialog.exec())
        {
        names = dialog.selectedFiles();
        this->ui->editFileName->setText(names.first());
        }
    }

void AddEditDbFileWindow::on_actionCreateNewDatabaseFile_triggered()
    {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Database (*.sqlite)"));
    dialog.setDefaultSuffix(".sqlite");
    QStringList names;
    if(dialog.exec())
        {
        names = dialog.selectedFiles();

        QMessageBox ask(this);
        ask.setText(tr("Woul'd You like to create new database file?"));
        ask.setStandardButtons(QMessageBox::No|QMessageBox::Yes);
        ask.setDefaultButton(QMessageBox::Yes);
        if(ask.exec() == QMessageBox::Yes)
            {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","vCheck");
            db.setDatabaseName(names.first());
            if(db.open())
                {
                QFile f(":/db/create.sql");
                if(f.open(QIODevice::ReadOnly))
                    {
                    QStringList commands = QString(f.readAll()).split(";");
                    f.close();

                    db.transaction();
                    QSqlQuery q(db);
                    for(int i=0; i< commands.count();i++)
                        {
                        QString c = commands.at(i).trimmed();
                        qDebug()<<"Execute command: "<<c;
                        if(!c.isEmpty())
                            {
                            q.prepare(c+";");
                            if(!q.exec())
                                {
                                qDebug()<<"error"<<db.lastError().text();
                                db.rollback();
                                db.close();
                                QSqlDatabase::removeDatabase("vCheck");
                                return;
                                }
                            }
                        qDebug()<<i;
                        }
                    db.commit();

                    }
                }
            db.close();
            QSqlDatabase::removeDatabase("vCheck");
            this->ui->editFileName->setText(names.first());
            }
        }
    }
