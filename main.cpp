#include <QApplication>
#include "gui/SelectDbWindow.h"

int main(int argc, char *argv[])
	{
	QApplication a(argc, argv);
	a.setApplicationVersion("0.0.1.2");
	a.setApplicationName("c3Networks");

	SelectDbWindow w;
	w.show();

	return a.exec();
	}
