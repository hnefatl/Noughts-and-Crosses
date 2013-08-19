#include "StatusMessages.h"

namespace StatusMessages
{
	namespace Generic
	{
		const std::string NewGameMessage="Start a new game from File on the menu.";
		const std::string Player1Turn="Player 1's turn.";
		const std::string Player2Turn="Player 2's turn.";
		const std::string Player1Win="Player 1 has won!";
		const std::string Player2Win="Player 2 has won!";
		const std::string Draw="There is a draw!";
	}
	namespace Net
	{
		const std::string WaitingForOpponent="Waiting for opponent to connect...";
		const std::string OpponentDisconnected="The opponent disconnected.";
		const std::string OpponentFailedToConnect="The opponent couldn't connect.";
	}
}