#pragma once
#include "Interface.h"
#include <iostream>
#include "Lanista.h"
class Game
{
	unsigned int number_of_players;
	Lanista *player_one;
	Lanista *current_player;
public:
	Game(unsigned int _number_of_players);
	void start();
};