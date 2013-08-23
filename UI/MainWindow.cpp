#include "MainWindow.h"

#include "Globals.h"
#include "StatusMessages.h"

#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "OnlinePlayer.h"

#include <sstream>

MainWindow::MainWindow(QWidget *Parent)
	:QWidget(Parent),
	ButtonPressed(false)
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
		// Set the online players IP and Port
		((OnlinePlayer *)Dialog_NewGame->GameOpponent)->SetData(Dialog_OnlinePlayerSettings->IP, Dialog_OnlinePlayerSettings->Port);
		delete Dialog_OnlinePlayerSettings;

		//Get the symbol of the Online player from the server
		std::string Received;
		((OnlinePlayer *)Dialog_NewGame->GameOpponent)->Receive(&Received);
		// Assign the opponent's symbol based on what character was received from the server
		Dialog_NewGame->GameOpponent->PlayerSymbol=Received=="0"?CellContents::Cross:CellContents::Nought;
		// Assign the player's symbol based on the symbol received from the server
		Dialog_NewGame->GamePlayer->PlayerSymbol=Received=="1"?CellContents::Cross:CellContents::Nought;
	}
	else
	{
		// Not an online player - set the symbols manually
		Dialog_NewGame->GamePlayer->PlayerSymbol=CellContents::Cross;
		Dialog_NewGame->GameOpponent->PlayerSymbol=CellContents::Nought;
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
	delete Dialog_NewGame; // Clean up

	// Disable all buttons
	for(unsigned int y=0; y<Buttons.size(); y++)
	{
		for(unsigned int x=0; x<Buttons.size(); x++)
		{
			// Disable button
			Buttons[y][x]->setEnabled(false);
			// Remove any text
			Buttons[y][x]->setText(QString());
		}
	}

	// Start the game on a new thread
	if(PlayingThread!=NULL)
	{
		delete PlayingThread;
	}
	PlayingThread=new GameThread(Players[0], Players[1], this);
	PlayingThread->start();
	return true;
}

Vector MainWindow::WaitForButtonPress()
{
	// Connect the functions
	for(unsigned int y=0; y<Buttons.size(); y++)
	{
		for(unsigned int x=0; x<Buttons[y].size(); x++)
		{
			connect(Buttons[y][x], &QPushButton::pressed, this, &MainWindow::_WaitForButtonPress);
		}
	}

	// Wait for button to be pressed
	while(!ButtonPressed)
	{
		Sleep(10);
	}

	// Disconnect the functions
	for(unsigned int y=0; y<Buttons.size(); y++)
	{
		for(unsigned int x=0; x<Buttons[y].size(); x++)
		{
			disconnect(Buttons[y][x], &QPushButton::pressed, this, &MainWindow::_WaitForButtonPress);
		}
	}

	return ButtonLocation;
}

void MainWindow::_WaitForButtonPress()
{
	// Obtain the sender object
	QObject *Sender=sender();
	// Check every button
	for(unsigned int y=0; y<GridSize; y++)
	{
		for(unsigned int x=0; x<GridSize; x++)
		{
			// If the pointers are the same
			if(Buttons[y][x]==Sender)
			{
				ButtonPressed=true;
				ButtonLocation.X=x;
				ButtonLocation.Y=y;
			}
		}
	}	
}

void MainWindow::SetButtonText(const Vector &Button, const QString &Text)
{
	Buttons[Button.X][Button.Y]->setText(Text);
	Buttons[Button.X][Button.Y]->update();
}
void MainWindow::SetButtonEnabled(const Vector &Button, const bool &Enabled)
{
	Buttons[Button.X][Button.Y]->setEnabled(Enabled);
}

void MainWindow::SetPressableButtonsEnabled(const bool &Enabled)
{
	for(unsigned int y=0; y<Buttons.size(); y++)
	{
		for(unsigned int x=0; x<Buttons[y].size(); x++)
		{
			// If the text is empty
			if(Buttons[y][x]->text()==QString())
			{
				Buttons[y][x]->setEnabled(Enabled);
			}
		}
	}
}

void MainWindow::SetStatusText(const QString &Text)
{
	Status->setText(Text);
	Status->update();
}