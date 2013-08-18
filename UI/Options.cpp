#include "options.h"

Options::Options(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Options::~Options()
{

}

void Options::show()
{
	ui.setupUi(parentWidget());
	QWidget::show();
}