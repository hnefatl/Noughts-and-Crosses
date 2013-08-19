#ifndef _NETWORKSETTINGS_H
#define _NETWORKSETTINGS_H

#include <QtWidgets\qwidget.h>
#include "GeneratedFiles\ui_NetworkSettings.h"

class NetworkSettings : public QWidget
{
	Q_OBJECT

public:
	NetworkSettings(QWidget *Parent=NULL);

private:
	Ui::Dialog_NetworkSettings ui;
};

#endif