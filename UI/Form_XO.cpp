#include "Form_XO.h"

Form_XO::Form_XO(QWidget *Parent)
	:QMainWindow(Parent),
	OptionsDialog(this),
	NetworkSettingsDialog(this)
{
	OptionsDialog.show();
}

void Form_XO::ShowOptions()
{
	OptionsDialog.show();
}