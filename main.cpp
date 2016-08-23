#include <QApplication>
#include "gui/SelectDbWindow.h"
#include "global/SettingsManager.h"

#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
    {
    QApplication a(argc, argv);
    a.setApplicationVersion("0.0.1.1");
    a.setApplicationName("c3Network");



    SelectDbWindow w;
    w.show();

    return a.exec();
    }
