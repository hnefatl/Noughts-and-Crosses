#include "NewGameDialog.h"

NewGameDialog::NewGameDialog(QWidget *Parent)
	:QDialog(Parent),
	ExitedLegally(false),
	GamePlayer(NULL),
	GameOpponent(NULL)
{
	Initialise();
}
NewGameDialog::~NewGameDialog()
{
}

void NewGameDialog::Initialise()
{
	resize(270, 150);
	setWindowTitle(QString("New game"));

	PlayerType=new QGroupBox(QString("Player Type"), this);
	PlayerType->setGeometry(10, 10, 120, 90);

	OpponentType=new QGroupBox(QString("Opponent Type"), this);
	OpponentType->setGeometry(140, 10, 120, 90);

	PlayerType_Human=new QRadioButton(QString("Human"), PlayerType);
	PlayerType_Human->setGeometry(10, 20, 80, 15);
	PlayerType_Human->setChecked(true);

	PlayerType_AI=new QRadioButton(QString("AI"), PlayerType);
	PlayerType_AI->setGeometry(10, 40, 80, 15);
	PlayerType_AI->setChecked(false);

	OpponentType_Human=new QRadioButton(QString("Human"), OpponentType);
	OpponentType_Human->setGeometry(10, 20, 80, 15);
	OpponentType_Human->setChecked(true);

	OpponentType_AI=new QRadioButton(QString("AI"), OpponentType);
	OpponentType_AI->setGeometry(10, 40, 80, 15);
	OpponentType_AI->setChecked(false);

	OpponentType_Online=new QRadioButton(QString("Online"), OpponentType);
	OpponentType_Online->setGeometry(10, 60, 80, 15);
	OpponentType_Online->setChecked(false);

	StartButton=new QPushButton(QString("Start"), this);
	StartButton->setGeometry(110, 110, 50, 25);
	connect(StartButton, SIGNAL(clicked()), this, SLOT(Exit()));
}

void NewGameDialog::Exit()
{
	ExitedLegally=true;
	
	// Decide on Player type
	if(PlayerType_Human->isChecked())
	{
		GamePlayer=new HumanPlayer();
	}
	else if(PlayerType_AI->isChecked())
	{
		GamePlayer=new AIPlayer();
	}

	// Decide on opponent type
	if(OpponentType_Human->isChecked())
	{
		GameOpponent=new HumanPlayer();
	}
	else if(OpponentType_AI->isChecked())
	{
		GameOpponent=new AIPlayer();
	}
	else if(OpponentType_Online->isChecked())
	{
		GameOpponent=new OnlinePlayer();
	}

	// Quit the dialog
	done(Accepted);
}