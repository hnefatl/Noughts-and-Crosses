#ifndef _CLIENT_H
#define _CLIENT_H

#include <string>



class Client
{
public:
	Client();

	bool Connect(std::string IP, std::string Port);

private:

};

#endif