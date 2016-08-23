#ifndef ADDEDITDBFILEWINDOW_H
#define ADDEDITDBFILEWINDOW_H

#include <QDialog>
#include <QMenu>

namespace Ui {
class AddEditDbFileWindow;
}

class AddEditDbFileWindow : public QDialog
    {
        Q_OBJECT
    public:
        explicit AddEditDbFileWindow(QWidget *parent = 0);
        ~AddEditDbFileWindow();
        void setData(int id, QString name, QString fileName, QString description);
    private slots:
        void on_buttonCancel_clicked();
        void on_buttonConfirm_clicked();

        void on_actionSelectDatabaseFile_triggered();

        void on_actionCreateNewDatabaseFile_triggered();

private:
        Ui::AddEditDbFileWindow *ui;
        int id;
        QMenu createMenu;
    signals:
        void addItem(QString name, QString fileName, QString description);
        void updateItem(int id, QString name, QString fileName, QString description);
    };

#endif // ADDEDITDBFILEWINDOW_H
