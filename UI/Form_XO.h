#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets\qwidget>
#include "GeneratedFiles\ui_Form_XO.h"
#include "GeneratedFiles\ui_Options.h"
#include "GeneratedFiles\ui_NetworkSettings.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private:
	Ui::Form_XO XO;
	Ui::Dialog_Options Options;
	Ui::Dialog_NetworkSettings NetworkSettings;
};

#endif