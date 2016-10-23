#ifndef ADDHOSTRANGEWINDOW_H
#define ADDHOSTRANGEWINDOW_H

#include <QDialog>
#include "../../database/IfDbTable.h"
#include "../../models/GrTableModel.h"
#include "../validators/IpValidator.h"
#include "../validators/NetMaskValidator.h"
#include <QCompleter>

namespace Ui { class AddRangeWindow; }

class AddRangeWindow : public QDialog
    {
        Q_OBJECT
    public:
        explicit AddRangeWindow(QWidget *parent = 0);
        ~AddRangeWindow();
    private slots:
        void on_button_apply_clicked();
        void on_button_cancel_clicked();
    private:
        Ui::AddRangeWindow *ui;
        quint32 network;
        quint32 mask;
        quint32 broadcast;
        QList<quint32> masks;
        GrTableModel *model;
        IpValidator ipValidator;
        NetMaskValidator netMaskValidator;
        QCompleter *maskCompleter;
    signals:
        void addInterfaces(quint32 from, quint32 to, quint32 mask, int group);
    };

#endif // ADDHOSTRANGEWINDOW_H
