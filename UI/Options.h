#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <QtWidgets/QWidget>
#include "GeneratedFiles\ui_Options.h"

class Options : public QWidget
{
	Q_OBJECT

public:
	Options(QWidget *parent = 0);
	~Options();

	void show();

private:
	Ui::Dialog_Options ui;
};

#endif // OPTIONS_H
