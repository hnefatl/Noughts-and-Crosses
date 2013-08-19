#include <QtWidgets/QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow *Main=new MainWindow();
	Main->show();
	return a.exec();
}
