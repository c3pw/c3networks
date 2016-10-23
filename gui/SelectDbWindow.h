#ifndef SELECTDBWINDOW_H
#define SELECTDBWINDOW_H

#include <QDialog>
#include "selectDb/DatabaseUpdateWindow.h"
#include "helpers/HtmlHelper.h"
#include "../models/DbFileModel.h"

namespace Ui {
class SelectDbWindow;
}

class SelectDbWindow : public QDialog
    {
        Q_OBJECT

    public:
        explicit SelectDbWindow(QWidget *parent = 0);
        ~SelectDbWindow();

    private slots:
        void on_buttonClose_clicked();
        void on_listDb_clicked(const QModelIndex &index);

        void on_buttonConfirm_clicked();

        void on_listDb_activated(const QModelIndex &index);

        void on_buttonAddItem_clicked();

        void on_buttonEditItem_clicked();

        void on_buttonRemoveItem_clicked();

private:
        Ui::SelectDbWindow *ui;
        DbFileModel model;
        HtmlHelper htmlHelper;
    };

#endif // SELECTDBWINDOW_H
