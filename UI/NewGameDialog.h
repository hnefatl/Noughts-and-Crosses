#ifndef _NEWGAMEDIALOG_H
#define _NEWGAMEDIALOG_H

#include <QtWidgets\qwidget.h>
#include <QtWidgets\qdialog.h>
#include <QtWidgets\qgroupbox.h>
#include <QtWidgets\qradiobutton.h>
#include <QtWidgets\qpushbutton.h>

#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "OnlinePlayer.h"

class NewGameDialog
	: public QDialog
{
	Q_OBJECT

public:
	NewGameDialog(QWidget *Parent=NULL);
	~NewGameDialog();

public:
	// Widgets
	QGroupBox *PlayerType;
	QGroupBox *OpponentType;
	QRadioButton *PlayerType_Human;
	QRadioButton *PlayerType_AI;
	QRadioButton *OpponentType_Human;
	QRadioButton *OpponentType_AI;
	QRadioButton *OpponentType_Online;
	QPushButton *StartButton;

	bool ExitedLegally;

	Player *GamePlayer;
	Player *GameOpponent;

private slots:
	void Exit();

private:
	void Initialise();

};

#endif