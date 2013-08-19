#include "MainWindow.h"

#include "Globals.h"
#include "StatusMessages.h"

#include <sstream>

MainWindow::MainWindow(QWidget *Parent)
	:QWidget(Parent)
{
	Initialise();
}
MainWindow::~MainWindow()
{
}

void MainWindow::Initialise()
{
	const int WindowWidth=265, WindowHeight=315;
	// Set dimensions of this window
	resize(WindowWidth, WindowHeight);
	// Set title to "XO"
	setWindowTitle(QString("XO"));

	// Set up StartNewGame action
	StartNewGame=new QAction(QString("New game..."), this);
	StartNewGame->setShortcut(QKeySequence(QString("Ctrl+N")));
	StartNewGame->setStatusTip(QString("Start a new game."));
	connect(StartNewGame, SIGNAL(triggered()), this, SLOT(NewGame()));

	// Set up Exit action
	Exit=new QAction(QString("Exit"), this);
	Exit->setShortcut(QKeySequence(QString("Alt+F4")));
	Exit->setStatusTip(QString("Exits the application."));
	connect(Exit, SIGNAL(triggered()), this, SLOT(quit()));

	// Set up FileMenu
	FileMenu=new QMenu(QString("File"), this);
	FileMenu->addAction(StartNewGame);
	FileMenu->addAction(Exit);

	// Set up Menu bar, setting the parent to this window
	MenuBar=new QMenuBar(this);
	// Set size
	MenuBar->setGeometry(0, 0, WindowWidth, 20);
	// Create a menu on it
	MenuBar->addMenu(FileMenu);

	// Set up the Status box, setting the parent to this window
	Status=new QLineEdit(this);
	// Position it on the window
	Status->setGeometry(10, 30, 245, 20);
	// Set read-only
	Status->setReadOnly(true);
	// Disable the box (no user interaction)
	Status->setEnabled(false);
	// Set the text to the initial message
	SetStatusText(StatusMessages::NewGameMessage);

	// Set up the array of buttons
	Buttons.resize(GridSize);
	for(unsigned int x=0; x<GridSize; x++)
	{
		Buttons[x].resize(GridSize);
	}
	// Initialise each button and change settings
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			// Initialise the button, setting the parent widget to this window
			Buttons[y][x]=new QPushButton(this);
			// Determine its name
			std::stringstream Name;
			Name<<"Button"<<y<<x;
			// Set the name
			Buttons[y][x]->setObjectName(QString(Name.str().c_str()));
			// Set the text to blank
			Buttons[y][x]->setText(QString());
			// Disable all buttons
			Buttons[y][x]->setEnabled(false);
			// Change geometry
			// Each button is 75x75 pixels. They need to start at (10, 40), and have a 10x10 gap between each one
			Buttons[y][x]->setGeometry(10+(85*x), 60+(85*y), 75, 75);
		}
	}
}

bool MainWindow::NewGame()
{
	return true;
}

void MainWindow::SetStatusText(std::string Text)
{
	Status->setText(QString(Text.c_str()));
}