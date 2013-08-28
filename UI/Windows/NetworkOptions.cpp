#include "NetworkOptions.h"

#include <iostream>
#include <conio.h>
#include <Networking.h>

#include "..\ConsoleControl.h"

NetworkOptions::NetworkOptions()
	:CurrentlySelected(0)
{
	IPText="Server IP: ";
	PortText="Server port: ";
}

UpdateResult NetworkOptions::Update()
{
	int KeyPressed=_getch();

	switch (KeyPressed)
	{
	case 224: // Special key
		KeyPressed=_getch(); // Get true key
		switch (KeyPressed)
		{
		case 72: // Up arrow
			if(CurrentlySelected>0)
				CurrentlySelected--;
			break;
		case 80: // Down arrow
			if(CurrentlySelected<1)
				CurrentlySelected++;
			break;
		}
		break;
	case 13: // Enter key
		if(IsValidInput())
		{
			return UpdateResult::urEnter; // Return success
		}
		break;
	case 27: // Escape key
		return UpdateResult::urEscape; // Return failure
	default:
		char NewCharacter=(char)KeyPressed;

		if(CurrentlySelected==0)
		{
			OldIP=IP;
			// If a backspace
			if(NewCharacter=='\b')
			{
				if(IP.size()>0)
				{
					// Erase the last character
					IP.erase(IP.size()-1);
				}
			}
			// Check the IP is not too long
			if(IP.size()<15)
			{
				// If valid input
				if(IsNumber(NewCharacter) || IsDot(NewCharacter))
				{
					// Append the new character to the actual string
					IP+=NewCharacter;
				}
			}
		}
		else
		{
			OldPort=Port;
			// Check the port is not too long
			if(NewCharacter=='\b')
			{
				if(Port.size()>0)
				{
					// Erase the last character
					Port.erase(Port.size()-1);
				}
			}
			if(Port.size()<5)
			{
				// If valid input
				if(IsNumber(NewCharacter))
				{
					// Append the new character to the actual string
					Port+=NewCharacter;
				}
			}
		}
		break;
	}

	return UpdateResult::urContinue;
}

void NetworkOptions::Draw(bool Initial)
{
	if(Initial)
	{
		Clear();
		SetCursor(1, 1);
		std::cout<<IPText;
		SetCursor(1, 3);
		std::cout<<PortText;
		SetCursor(1+IPText.size(), 1);
	}
	else
	{
		if(CurrentlySelected==0)
		{
			SetCursor(IPText.size()+1, 1);
			std::cout<<IP;
			// New IP is shorter than the last one
			if(OldIP.size()>IP.size())
			{
				// Remove all excess characters
				for(unsigned int x=1; x<=OldIP.size()-IP.size(); x++)
				{
					SetCursor(IPText.size()+1+OldIP.size()-x, 1);
					std::cout<<" ";
				}
			}
			// Place cursor at correct position
			SetCursor(IPText.size()+1+IP.size(), 1);
		}
		else
		{
			SetCursor(PortText.size()+1, 3);
			std::cout<<Port;
			// New Port is shorter than the last one
			if(OldPort.size()>Port.size())
			{
				// Remove all excess characters
				for(unsigned int x=1; x<=OldPort.size()-Port.size(); x++)
				{
					SetCursor(IPText.size()+1+OldPort.size()-x, 1);
					std::cout<<" ";
				}
			}
			// Place cursor at correct position
			SetCursor(PortText.size()+1+Port.size(), 3);
		}
	}
}

bool NetworkOptions::IsNumber(char Input)
{
	// Loop through all ASCII representtions of digits
	for(char x=48; x<=57; x++)
	{
		if(Input==x)
		{
			return true;
		}
	}

	return false;
}
bool NetworkOptions::IsDot(char Input)
{
	return Input=='.';
}
bool NetworkOptions::IsValidInput()
{
	if(!Net::ValidIP(IP))
	{
		// If the IP isn't valid
		return false;
	}
	if(Port.size()==0)
	{
		return false;
	}
	for(unsigned int x=0; x<Port.size(); x++)
	{
		// If the digit is not a number
		if(!IsNumber(Port[x]))
		{
			return false;
		}
	}
	return true;
}