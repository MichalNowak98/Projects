#include "Interface.h"

std::string ask_for_name()
{
	std::cout << "What is your name?:\t";
	std::string name;
	std::cin >> name;
	system("cls");
	return name;
}

unsigned int ask_for_number_of_players()
{
	std::cout << "Number of players:\t";
	unsigned int number_of_players;
	std::cin >> number_of_players;
	system("cls");
	return number_of_players;
}