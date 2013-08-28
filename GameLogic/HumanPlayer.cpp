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
	// Nothing needs to be done - it should be handled by the program
	return ""; // Return no error
}

std::string HumanPlayer::InformMove(Grid *NewState)
{
	// Nothing needs to be done - it should be drawn by the program
	return ""; // Return no error
}