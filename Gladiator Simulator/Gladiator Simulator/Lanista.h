#pragma once
#include <iostream>
#include <vector>
#include "Gladiators.h"
#include "Interface.h"
class Lanista
{
	unsigned int denarii;
	std::string name;
	std::vector<Gladiator*> gladiators;
	Lanista* next_player;
public:
	Lanista();
	void create_next_player()
	{
		next_player = new Lanista;
	}
	void set_next_player(Lanista *_next_player);

	Lanista* get_next_player() const;
};