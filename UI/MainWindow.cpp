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
	Play();
	return true;
}

bool MainWindow::Play()
{
	if(Players.size()!=2)
	{
		return false;
	}

	Players[0]->Initialise();
	if(Players[1]->Type==PlayerType::Online)
	{
		SetStatusText(StatusMessages::Net::WaitingForOpponent);
	}
	if(Players[1]->Initialise()!="")
	{
		SetStatusText(StatusMessages::Net::OpponentFailedToConnect);
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

		// If we are waiting for a human move, enable the buttons
		if(Players[CurrentPlayer]->Type==PlayerType::Human)
		{
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
						Buttons[y][x]->repaint();
					}
				}
			}
		}
		Move ChosenMove;
		// Non-human player
		if(Players[CurrentPlayer]->Type!=PlayerType::Human)
		{
			// If something went wrong
			if(Players[CurrentPlayer]->GetMove(&ChosenMove)!="")
			{
				SetStatusText("Error");
				return false;
			}
		}
		else
		{
			// Human player
			// Wait for a button to be pressed
			// Loop through all buttons
			for(unsigned int y=0; y<GridSize; y++)
			{
				for(unsigned int x=0; x<GridSize; x++)
				{
					// If the button has not been pressed yet
					if(Buttons[y][x]->text().toStdString()=="")
					{
						// Connect the trigger to the function
						connect(Buttons[y][x], &QPushButton::clicked, this, &MainWindow::WaitForButtonPress);
					}
				}
			}

			// Now wait for "ButtonPressed" to become true
			while(!ButtonPressed)
			{
				Sleep(10); // Slightly ease off the CPU
			}

			// Disable the triggers
			// Loop through all the buttons
			for(unsigned int y=0; y<GridSize; y++)
			{
				for(unsigned int x=0; x<GridSize; x++)
				{
					// If the button has not been pressed yet
					if(Buttons[y][x]->text().toStdString()=="")
					{
						// Disconnect the trigger from the function
						disconnect(Buttons[y][x], &QPushButton::clicked, this, &MainWindow::WaitForButtonPress);
					}
				}
			}

			// Store the necessary data in ChosenMove
			ChosenMove.Position=ButtonLocation;
			ChosenMove.Value=Players[CurrentPlayer]->PlayerSymbol;

			// Reset the storage variables
			ButtonPressed=false;
			ButtonLocation=Vector();
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

		// Disable the buttons if the player was human
		if(Players[CurrentPlayer]->Type==PlayerType::Human)
		{
			for(unsigned int y=0; y<GridSize; y++)
			{
				for(unsigned int x=0; x<GridSize; x++)
				{
					// Disable the button
					Buttons[y][x]->setEnabled(false);
					Buttons[y][x]->repaint();
				}
			}
		}
		// Swap player
		CurrentPlayer==0?CurrentPlayer=1:CurrentPlayer=0;
	}

	// Game is over
	if(Board.IsGoalState(Players[0]->PlayerSymbol))
	{
		SetStatusText(StatusMessages::Generic::Player1Win);
	}
	else if(Board.IsGoalState(Players[1]->PlayerSymbol))
	{
		SetStatusText(StatusMessages::Generic::Player2Win);
	}
	else
	{
		SetStatusText(StatusMessages::Generic::Draw);
	}

	return true;
}

void MainWindow::WaitForButtonPress()
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

void MainWindow::SetStatusText(std::string Text)
{
	Status->setText(QString(Text.c_str()));
	Status->repaint();
}