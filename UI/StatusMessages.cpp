#include "StatusMessages.h"

namespace StatusMessages
{
	namespace Generic
	{
		const QString NewGameMessage=QString("Start a new game from File on the menu.");
		const QString Player1Turn=QString("Player 1's turn.");
		const QString Player2Turn=QString("Player 2's turn.");
		const QString Player1Win=QString("Player 1 has won!");
		const QString Player2Win=QString("Player 2 has won!");
		const QString Draw=QString("There is a draw!");
	}
	namespace Net
	{
		const QString WaitingForOpponent=QString("Waiting for opponent to connect...");
		const QString OpponentDisconnected=QString("The opponent disconnected.");
		const QString OpponentFailedToConnect=QString("The opponent couldn't connect.");
	}
}