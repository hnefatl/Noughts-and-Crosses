#include <iostream>
#include <ctime>

#include "Server.h"

int main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));
	std::string IP=argc>0?argv[0]:"127.0.0.1";
	std::string Port="34652";
	Server Serv;
	Serv.Start(IP, Port, 10);
	
	return 0;
}