#include "options.h"

Options::Options(QWidget *parent)
	: QWidget(parent)
{

}

Options::~Options()
{

}

void Options::show()
{
	QWidget *Widget=new QWidget();
	ui.setupUi(Widget);
	Widget->show();
	QWidget::show();
}