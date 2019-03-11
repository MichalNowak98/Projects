#include "Game.h"
#include "Lanista.h"

Game::Game(unsigned int _number_of_players): number_of_players(_number_of_players)
{
	if (number_of_players == 0)
		throw std::invalid_argument("At least one player");
	Lanista *player_one;
}
