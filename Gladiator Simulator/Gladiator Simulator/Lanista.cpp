#include "Lanista.h"

Lanista::Lanista(): next_player(nullptr), denarii(10000)
{
	name = ask_for_name();
}

void Lanista::set_next_player(Lanista *_next_player)
{
	next_player = _next_player;
}

Lanista* Lanista::get_next_player() const
{
	return next_player;
}
