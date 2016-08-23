#ifndef EXPORTWINDOW_H
#define EXPORTWINDOW_H

#include <QDialog>

namespace Ui {
class ExportWindow;
}

class ExportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ExportWindow(QWidget *parent = 0);
    ~ExportWindow();

private slots:
    void on_buttonCancel_clicked();

    void on_buttonFileName_clicked();

    void on_buttonExport_clicked();

signals:
    void exportAllToCSV(QString filename,bool chId, bool chIp, bool chMask, bool chName, bool chMac,
                            bool chUser, bool chDomain, bool chLocation, bool chDhcp, bool chDescription,
                                bool header, bool numbers, QString separator);

private:
    Ui::ExportWindow *ui;
};

#endif // EXPORTWINDOW_H
