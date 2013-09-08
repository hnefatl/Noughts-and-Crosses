#include <iostream>
#include <ctime>
#include <conio.h>

#include <vector>
#include <string>

#include "Server.h"
#include "ConsoleControl.h"

std::string GetIP(std::vector<std::string> *Addresses);

int main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));
	Server Serv;
	// Make the user choose the local address to use
	EnableCursor(false);
	std::string IP=argc>1?argv[1]:GetIP(Serv.GetLocalAddresses());
	EnableCursor(true);
	std::string Port=argc>2?argv[2]:"34652";

	if(IP=="")
	{
		// Quit
		return 0;
	}

	Clear();
	Serv.Start(IP, Port, 10);

	_getch();
	return 0;
}

std::string GetIP(std::vector<std::string> *Addresses)
{
	if(Addresses==NULL)
	{
		return "";
	}
	unsigned int Selected=0, LastSelected=0;

	for(unsigned int x=0; x<Addresses->size(); x++)
	{
		std::cout<<" "<<Addresses->at(x)<<std::endl;
	}

	while(true)
	{
		// Clear last cursor
		SetCursor(0, LastSelected);
		std::cout<<" ";

		// Set new cursor
		SetCursor(0, Selected);
		std::cout<<">";

		LastSelected=Selected;

		int KeyPressed=_getch();
		switch(KeyPressed)
		{
		case 224:
			KeyPressed=_getch();

			switch(KeyPressed)
			{
			case 72: // Up arrow
				if(Selected>0)
					Selected--;
				break;

			case 80: // Down arrow
				if(Selected<Addresses->size()-1)
					Selected++;
				break;
			}
			break;

		case 13: // Enter
			return Addresses->at(Selected);

		case 27:
			return "";
		}
	}
}