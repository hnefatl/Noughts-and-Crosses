#include <QtWidgets/QApplication>
#include <QtWidgets\qmainwindow.h>
#include "ui_Form_XO.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMainWindow *Window=new QMainWindow();
	Ui::Form_XO XOWindow;

	XOWindow.setupUi(Window);
	Window->show();
	
	return a.exec();
}
