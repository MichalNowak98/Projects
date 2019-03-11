#include "Game.h"

Game::Game(unsigned int _number_of_players): number_of_players(_number_of_players)
{
	if (number_of_players == 0)
		throw std::invalid_argument("At least one player");
	player_one = new Lanista;
	current_player = player_one;
	for (int iterator = 1; iterator < number_of_players; iterator++)
	{
		current_player->create_next_player();
		current_player = current_player->get_next_player();
	}
	current_player->set_next_player(player_one);
	current_player = player_one;
}
