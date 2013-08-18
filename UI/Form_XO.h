#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets\qwidget>
#include "GeneratedFiles\ui_Form_XO.h"
#include "Options.h"
#include "NetworkSettings.h"

class Form_XO : public QMainWindow
{
	Q_OBJECT

public:
	Form_XO(QWidget *Parent=NULL);

public slots:
	void ShowOptions();

private:
	Ui::Form_XO XO;
	Options OptionsDialog;
	NetworkSettings NetworkSettingsDialog;
};

#endif