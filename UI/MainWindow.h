#ifndef _MANIWINDOW_H
#define _MAINWINDOW_H

#include <QtWidgets\qwidget.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qmenubar.h>

#include <vector>

class MainWindow
	: public QWidget
{
public:
	MainWindow(QWidget *Parent=NULL);
	~MainWindow();

	void SetStatusText(std::string Text);

public:
	QMenuBar *MenuBar;
	QMenu *FileMenu;
	QAction *StartNewGame;
	QLineEdit *Status;
	std::vector<std::vector<QPushButton *>> Buttons;

private:
	void Initialise();

	bool NewGame();
};

#endif