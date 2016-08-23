#ifndef GROUPSMANAGERWINDOWS_H
#define GROUPSMANAGERWINDOWS_H

#include <QDialog>
#include "../../models/GrTableModel.h"

namespace Ui {
class GropusManagerWindow;
}

class GropusManagerWindow : public QDialog
    {
        Q_OBJECT

    public:
        explicit GropusManagerWindow(QWidget *parent = 0);
        ~GropusManagerWindow();

    private slots:
        void on_buttonClose_clicked();

        void on_buttonAddGroup_clicked();

        void on_buttonEditGroup_clicked();

        void on_buttonRemoveGroup_clicked();

    private:
        Ui::GropusManagerWindow *ui;
        GrTableModel *model;

    signals:
        void deleteGroup(int id);
    };

#endif // GROUPSMANAGERWINDOWS_H
