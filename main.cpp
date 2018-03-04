#include <QApplication>
#include "gui/SelectDbWindow.h"
#include <QtDebug>

int main(int argc, char *argv[])
	{
	QApplication a(argc, argv);
	a.setApplicationVersion("0.0.1.3");
	a.setApplicationName("c3Networks");

	qDebug()<<"test";

	SelectDbWindow w;
	w.show();

	return a.exec();
	}
