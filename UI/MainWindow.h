#ifndef _MANIWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets\qwidget.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qmenubar.h>

#include <vector>
#include <thread>

#include "Grid.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "OnlinePlayer.h"

#include "NewGameDialog.h"
#include "OnlinePlayerSettingDialogs.h"

#include "GameThread.h"

class MainWindow
	: public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *Parent=NULL);
	~MainWindow();

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
public slots:
	bool NewGame();

	Vector WaitForButtonPress();

	void SetButtonText(const Vector &Button, const QString &Text);
	void SetButtonEnabled(const Vector &Button, const bool &Enabled);

	void SetPressableButtonsEnabled(const bool &Enabled);

	void SetStatusText(const QString &Text);

private slots:
	void _WaitForButtonPress();

private:
	void Initialise();

	bool ButtonPressed;
	Vector ButtonLocation;

	GameThread *PlayingThread;
};

#endif