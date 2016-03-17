#include "mainwidget.h"

#include <QtGui>
#include <QtWidgets/QApplication>
#include <QDesktopWidget>
#include <QObject>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWidget w;
	w.show();
	QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(exitHandler()));
	return a.exec();
}
