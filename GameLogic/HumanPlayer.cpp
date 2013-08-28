#include "HumanPlayer.h"

HumanPlayer::HumanPlayer()
	:Player(PlayerType::Human)
{

}
HumanPlayer::~HumanPlayer()
{

}

std::string HumanPlayer::Initialise()
{
	// Nothing needs to be done
	return ""; // Return no error
}

std::string HumanPlayer::GetMove(Move *ChosenMove)
{
	// Get input

	return ""; // Return no error
}

std::string HumanPlayer::InformMove(Grid *NewState)
{
	// Nothing needs to be done - it should be drawn by the program anyway
	return ""; // Return no error
}