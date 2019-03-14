#pragma once
#include "Interface.h"
#include <iostream>
#include "Lanista.h"
class Game
{
	unsigned int number_of_players;
	unsigned int size_of_gladiator_market;
	Lanista *player_one;
	Lanista *current_player;
	std::vector<Gladiator*> market;
public:
	Game(unsigned int _number_of_players);
	void play();
	void fill_market();
};