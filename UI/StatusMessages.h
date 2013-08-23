#ifndef _STATUSMESSAGES_H
#define _STATUSMESSAGES_H

#include <qstring.h>

namespace StatusMessages
{
	namespace Generic
	{
		extern const QString NewGameMessage;
		extern const QString Player1Turn;
		extern const QString Player2Turn;
		extern const QString Player1Win;
		extern const QString Player2Win;
		extern const QString Draw;
	}
	namespace Net
	{
		extern const QString OpponentDisconnected;
		extern const QString WaitingForOpponent;
		extern const QString OpponentFailedToConnect;
	}
}
#endif