#include "options.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Options w;
	w.show();
	return a.exec();
}
