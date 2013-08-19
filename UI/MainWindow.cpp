#include "MainWindow.h"

#include "Globals.h"
#include "StatusMessages.h"

#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "OnlinePlayer.h"

#include <sstream>

MainWindow::MainWindow(QWidget *Parent)
	:QWidget(Parent)
{
	Players.resize(2); // Make room for two players
	Initialise();
}
MainWindow::~MainWindow()
{
	delete MenuBar;
	delete FileMenu;
	delete StartNewGame;
	delete Exit;
	delete Status;
	for(unsigned int y=0; y<Buttons.size(); y++)
	{
		for(unsigned int x=0; x<Buttons[y].size(); x++)
		{
			delete Buttons[y][x];
		}
	}
}

void MainWindow::Initialise()
{
	const int WindowWidth=265, WindowHeight=315;
	// Set dimensions of this window
	resize(WindowWidth, WindowHeight);
	// Set title to "XO"
	setWindowTitle(QString("XO"));

	// Set up Menu bar, setting the parent to this window
	MenuBar=new QMenuBar(this);
	// Set up FileMenu, setting the parent to MenuBar
	FileMenu=new QMenu(QString("File"), MenuBar);

	// Set up StartNewGame action, setting its parent as FileMenu
	StartNewGame=new QAction(QString("New game..."), FileMenu);
	StartNewGame->setShortcut(QKeySequence(QString("Ctrl+N")));
	StartNewGame->setStatusTip(QString("Start a new game."));
	connect(StartNewGame, SIGNAL(triggered()), this, SLOT(NewGame()));

	// Set up Exit action, setting its parent as FileMenu
	Exit=new QAction(QString("Exit"), FileMenu);
	Exit->setShortcut(QKeySequence(QString("Alt+F4")));
	Exit->setStatusTip(QString("Exits the application."));
	connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

	// Set up FileMenu
	FileMenu->addAction(StartNewGame);
	FileMenu->addAction(Exit);

	// Menubar
	// Set size
	MenuBar->setGeometry(0, 0, WindowWidth, 21);
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
	SetStatusText(StatusMessages::Generic::NewGameMessage);

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
	// Show the dialog (modal is set in its initialisation stage)
	NewGameDialog *Dialog_NewGame=new NewGameDialog(this);
	Dialog_NewGame->exec();
	if(!Dialog_NewGame->ExitedLegally)
	{
		// Exited without agreeing
		return false;
	}

	if(Dialog_NewGame->GameOpponent->Type==PlayerType::Online)
	{
		// The opponent is an online player
		OnlinePlayerSettingsDialog *Dialog_OnlinePlayerSettings=new OnlinePlayerSettingsDialog();
		Dialog_OnlinePlayerSettings->exec();
		if(!Dialog_OnlinePlayerSettings->ExitedLegally)
		{
			delete Dialog_OnlinePlayerSettings;
			// Exited without agreeing
			return false;
		}
		((OnlinePlayer *)Dialog_NewGame->GameOpponent)->SetData(Dialog_OnlinePlayerSettings->IP, Dialog_OnlinePlayerSettings->Port);
		delete Dialog_OnlinePlayerSettings;
	}
	// No going back - the players have been chosen

	// Reset the players
	for(unsigned int x=0; x<Players.size(); x++)
	{
		if(Players[x]!=NULL)
		{
			delete Players[x];
			Players[x]=NULL;
		}
	}
	// Assign our new players
	Players[0]=Dialog_NewGame->GamePlayer;
	Players[1]=Dialog_NewGame->GameOpponent;

	// Disable all buttons
	for(unsigned int y=0; y<Buttons.size(); y++)
	{
		for(unsigned int x=0; x<Buttons.size(); x++)
		{
			// Disable
			Buttons[y][x]->setEnabled(false);
			// Remove any text
			Buttons[y][x]->setText(QString());
		}
	}

	delete Dialog_NewGame;

	return Play();
}

bool MainWindow::Play()
{
	if(Players.size()!=2)
	{
		return false;
	}

	unsigned int CurrentPlayer=0;
	unsigned int CellsFilled=0;
	// While not won and the board is not full
	while((!Board.IsGoalState(CellContents::Cross) || !Board.IsGoalState(CellContents::Nought)) && CellsFilled!=GridSize*GridSize)
	{
		if(CurrentPlayer==0)
		{
			SetStatusText(StatusMessages::Generic::Player1Turn);
		}
		else
		{
			SetStatusText(StatusMessages::Generic::Player2Turn);
		}
		// Enable buttons
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				// If button has not been pressed
				if(Buttons[y][x]->text().toStdString()=="")
				{
					// Enable the button
					Buttons[y][x]->setEnabled(true);
				}
			}
		}
		Move ChosenMove;
		if(Players[CurrentPlayer]->Type!=PlayerType::Human)
		{
			// Non-human player
			Players[CurrentPlayer]->GetMove(&ChosenMove);
		}
		else
		{
			// Human player
			// Wait for a button to be pressed
		}
		// Set new "virtual" value
		Board.Board[ChosenMove.Position.Y][ChosenMove.Position.X].Set(ChosenMove.Value);
		CellsFilled++;
		// Set new "physical" value
		Buttons[ChosenMove.Position.Y][ChosenMove.Position.X]->setEnabled(false);
		Buttons[ChosenMove.Position.Y][ChosenMove.Position.X]->setText(QString(ChosenMove.Value==CellContents::Cross?"X":"O"));

		// Inform all players of the new state
		for(unsigned int x=0; x<Players.size(); x++)
		{
			Players[x]->InformMove(&Board);
		}

		// Swap player
		CurrentPlayer==0?CurrentPlayer=1:CurrentPlayer=0;
		// Disable the buttons
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				// If button has not been pressed
				if(Buttons[y][x]->text().toStdString()=="")
				{
					// Disable the button
					Buttons[y][x]->setEnabled(false);
				}
			}
		}
	}
	// Game is over
	if(Board.IsGoalState(CellContents::Cross))
	{

	}

	return true;
}

void MainWindow::SetStatusText(std::string Text)
{
	Status->setText(QString(Text.c_str()));
}