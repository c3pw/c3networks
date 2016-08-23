#ifndef CHANGEGROUP_H
#define CHANGEGROUP_H

#include <QDialog>
#include "../../models/GrTableModel.h"

namespace Ui {
class ChangeGroupWindow;
}

class ChangeGroupWindow : public QDialog
    {
        Q_OBJECT

    public:
        explicit ChangeGroupWindow(QWidget *parent = 0);
        ~ChangeGroupWindow();

        void setIdxList(const QList<int> &value);

    private slots:
        void on_buttonCancel_clicked();

        void on_buttonApply_clicked();

    private:
        Ui::ChangeGroupWindow *ui;
        GrTableModel model;
        QList<int> idx;
    signals:
        void changeGroup(QList<int>,int);
    };

#endif // CHANGEGROUP_H
