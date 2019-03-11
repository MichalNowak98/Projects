#include "Gladiators.h"
#include "Game.h"
int main()
{
	srand(time(NULL));
	Game game(ask_for_number_of_players());
	return 0;
}