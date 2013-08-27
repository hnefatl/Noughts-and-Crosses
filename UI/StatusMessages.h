#ifndef _STATUSMESSAGES_H
#define _STATUSMESSAGES_H

#include <string>

namespace StatusMessages
{
	namespace Generic
	{
		extern const std::string NewGameMessage;
		extern const std::string Player1Turn;
		extern const std::string Player2Turn;
		extern const std::string Player1Win;
		extern const std::string Player2Win;
		extern const std::string Draw;
	}
	namespace Net
	{
		extern const std::string OpponentDisconnected;
		extern const std::string WaitingForOpponent;
		extern const std::string OpponentFailedToConnect;
	}
}
#endif