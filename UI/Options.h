#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtWidgets/QWidget>
#include "ui_options.h"

class Options : public QWidget
{
	Q_OBJECT

public:
	Options(QWidget *parent = 0);
	~Options();

private:
	Ui::OptionsClass ui;
};

#endif // OPTIONS_H
