#include "Gladiators.h"
#include "Game.h"
int main()
{
	srand(time(NULL));
	Game game(ask_for_number_of_players());
	Smart_container<Gladiator> gladiators(new Gladiator(1,1));
	gladiators.push_back(new Gladiator(10, 100));
	game.play();
	return 0;
}