#include "PlayerChoiceWindow.h"

#include <iostream>
#include <conio.h>

#include "../ConsoleControl.h"

// Column

Column::Column()
	:Title(""),
	Position(),
	CurrentSelection(0),
	PreviousSelection(0)
{
}
Column::Column(std::string Title, Vector Position)
	:Title(Title),
	Position(Position),
	CurrentSelection(0),
	PreviousSelection(0)
{
}

void Column::ChangeSelection(unsigned int NewSelection)
{
	PreviousSelection=CurrentSelection;
	CurrentSelection=NewSelection;
}

void Column::Draw(bool Selected)
{
	// Draw the title
	DrawTitle(Selected);

	// Draw all contents
	for(unsigned int x=0; x<Contents.size(); x++)
	{
		// Draw it at the current position, and it's selected if the iterator matches the number that is selected
		DrawContent(x, x==CurrentSelection);
	}
}
void Column::DrawTitle(bool Selected)
{
	// Align the title
	SetCursor(Position.X, Position.Y);
	// Choose colour
	if(Selected)
	{
		SetColour(GREEN, BLACK);
	}
	else
	{
		SetColour(GREY, BLACK);
	}
	// Draw the title
	std::cout<<Title;
	// Reset the colour
	SetColour(GREY, BLACK);
}
void Column::DrawContent(unsigned int ContentNumber, bool Selected)
{
	// Align the content, at a depth of the title plus the content number
	SetCursor(Position.X, Position.Y+ContentNumber+1);
	// Choose colour
	if(Selected)
	{
		SetColour(GREEN, BLACK);
	}
	else
	{
		SetColour(GREY, BLACK);
	}
	// Draw content
	std::cout<<Contents[ContentNumber];
	// Reset colour
	SetColour(GREY, BLACK);
}

void Column::Update()
{
	// Redraw the newly unselected content
	DrawContent(PreviousSelection, false);
	// Redraw the newly selected content
	DrawContent(CurrentSelection, true);
}

// PlayerChoiceWindow

PlayerChoiceWindow::PlayerChoiceWindow()
	:Window(),
	CurrentColumn(0)
{
	// First column - Player Type, and position will always be the same
	Columns.push_back(Column("Player Type:", Vector(1, 1)));
	Columns[0].Contents.push_back("Human");
	Columns[0].Contents.push_back("AI");

	// Second column - Opponent Type, and position will be determined later (use a stub for now)
	Columns.push_back(Column("Opponent Type:", Vector()));
	Columns[1].Contents.push_back("Human");
	Columns[1].Contents.push_back("AI");
	Columns[1].Contents.push_back("Online");
}

UpdateResult PlayerChoiceWindow::Update()
{
	// Wait for key press
	int KeyPress=_getch();

	switch (KeyPress)
	{
	case 224: // Special key
		KeyPress=_getch(); // Get the true value
		switch(KeyPress)
		{
		case 72: // Up arrow
			// Check to see if it's a valid move
			if(Columns[CurrentColumn].CurrentSelection>0)
			{
				Columns[CurrentColumn].ChangeSelection(Columns[CurrentColumn].CurrentSelection-1);
			}
			break;
		case 80: // Down arrow
			// Check to see it it's a valid move
			if(Columns[CurrentColumn].CurrentSelection<Columns[CurrentColumn].Contents.size()-1)
			{
				Columns[CurrentColumn].ChangeSelection(Columns[CurrentColumn].CurrentSelection+1);
			}
			break;
		case 75: // Left arrow
			// Check to see if it's a valid move
			if(CurrentColumn>0)
			{
				PreviousColumn=CurrentColumn;
				CurrentColumn--;
			}
			break;
		case 77: // Right arrow
			// Check to see if it's a valid move
			if(CurrentColumn<Columns.size()-1)
			{
				PreviousColumn=CurrentColumn;
				CurrentColumn++;
			}
			break;
		}
		break;
	case 13: // Enter
		// Create the players
		GetPlayersFromSelection();
		return UpdateResult::urEnter; // Exit
	case 27: // Escape
		return UpdateResult::urEscape;
	}

	return UpdateResult::urContinue;
}
void PlayerChoiceWindow::Draw(bool Initial)
{
	if(Initial)
	{
		// Find the longest word used for the player types
		unsigned int OpponentColumnOffset=0;
		for(unsigned int x=0; x<Columns[0].Contents.size(); x++)
		{
			if(Columns[0].Contents[x].size()>OpponentColumnOffset)
			{
				OpponentColumnOffset=Columns[x].Contents[x].size();
			}
		}
		// Perform the same check as above only on the title
		if(Columns[0].Title.size()>OpponentColumnOffset)
		{
			OpponentColumnOffset=Columns[0].Title.size();
		}
		// Add some spacing to the end of the first column
		OpponentColumnOffset+=5;
		Columns[1].Position=Vector(OpponentColumnOffset, 1);

		// Draw the player types (1 in from the top, one in from the left), initially selected
		Columns[0].Draw(true);

		// Draw the opponent types (1 down from the top, as left as needs be), initially unselected
		Columns[1].Draw(false);
	}
	else
	{
		// Update the selection
		Columns[CurrentColumn].Update();

		// If a column switch has taken place
		if(PreviousColumn!=CurrentColumn)
		{
			for(unsigned int x=0; x<Columns.size(); x++)
			{
				// Redraw the title for all columns, checking for whether it's the current one
				Columns[x].DrawTitle(CurrentColumn==x);
			}
		}
	}
}

void PlayerChoiceWindow::GetPlayersFromSelection()
{
	std::string Player=Columns[0].Contents[Columns[0].CurrentSelection];
	if(Player=="Human")
		PlayerOne=new HumanPlayer();
	else if(Player=="AI")
		PlayerOne=new AIPlayer();

	std::string Opponent=Columns[1].Contents[Columns[1].CurrentSelection];
	if(Opponent=="Human")
		PlayerTwo=new HumanPlayer();
	else if (Opponent=="AI")
		PlayerTwo=new AIPlayer();
	else
		PlayerTwo=new OnlinePlayer();
}