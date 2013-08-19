#ifndef _MANIWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets\qwidget.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qmenubar.h>

#include <vector>

#include "Grid.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "OnlinePlayer.h"

#include "NewGameDialog.h"

class MainWindow
	: public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *Parent=NULL);
	~MainWindow();

	void SetStatusText(std::string Text);

public:
	// Widgets
	QMenuBar *MenuBar;
	QMenu *FileMenu;
	QAction *StartNewGame;
	QAction *Exit;

	QLineEdit *Status;
	std::vector<std::vector<QPushButton *>> Buttons;

	// Variables
	Grid Board;
	std::vector<Player *> Players;
	NewGameDialog *Dialog_NewGame;

private:
	void Initialise();

private slots:
	bool NewGame();
};

#endif