#include "Gladiators.h"

Gladiator::Gladiator(unsigned int _level, unsigned int _fame) : max_base_health(250 + random_int(25 * _level, 25 * _level + 100)),
base_stamina(50 + random_int(5 * _level, 5 * _level + 10)), base_strength(random_int(_level, _level * 3)),
base_dexterity(random_int(_level, _level * 3)), base_attack(5 + random_int(3 * _level, 3 * _level + 4)), adrenaline(0),
base_defence(random_int(_level * 3, _level * 3 + 5)), fame(_fame), level(_level), weapon(nullptr), shield(nullptr), left_hand(Unussigned), rigth_hand(Unussigned)
{
	asking_price = calculate_asking_price();
	max_health = max_base_health;
	stamina = base_stamina;
	strength = base_strength;
	attack = base_attack;
	defence = base_defence;
}
Gladiator::~Gladiator()
{
}

/*Gladiator::Gladiator(int _base_health, int _base_stamina, int _base_adrenaline, int _base_dexterity, int _base_strength, int _base_fame) :
	health(_base_health), stamina(_base_stamina), adrenaline(_base_adrenaline), dexterity(_base_dexterity), strength(_base_strength), fame(_base_fame) {};
*/
bool Gladiator::if_dead() const
{
	if (max_health > 0)
		return false;
	return true;
}

bool Gladiator::if_opponent_dead(Gladiator & opponent) const
{
	if (opponent.if_dead())
	{
		//add_fame(1/*jakis przelicznik*/);
		return true;
	}
	return false;
}

unsigned int Gladiator::calculate_asking_price() const
{
	return (max_base_health/2 + (base_attack + base_defence + base_strength + base_defence) * 5 + random_int(0, 100));
}

Thracian::Thracian(unsigned int _level, unsigned int _fame) : Gladiator(_level, _fame), dexterity_bonus(random_int(30, 40))
{
	dexterity += base_dexterity * dexterity_bonus;
}

Gaul::Gaul(unsigned int _level, unsigned int _fame) : Gladiator(_level, _fame), health_bonus(random_int(15, 20)), strength_bonus(random_int(20, 30))
{
	max_health += max_base_health * health_bonus;
	strength += base_strength * strength_bonus;
}

Samnite::Samnite(unsigned int _level, unsigned int _fame) : Gladiator(_level, _fame), defense_bonus(random_int(20, 30))
{
	defence += base_defence * defense_bonus;
}

Roman::Roman(unsigned int _level, unsigned int _fame) : Gladiator(_level, _fame), attack_bonus(random_int(20, 35))
{
	attack += base_attack * attack_bonus;
}

Gladiator* create_gladiator()
{
	switch (int random = random_int(0, 3))
	{
	case 0:
	{
		return new Roman(1, 0);
		break;
	}
	case 1:
	{
		return new Gaul(1, 0);
		break;
	}
	case 2:
	{
		return new Samnite(1, 0);
		break;
	}
	case 3:
	{
		return new Thracian(1, 0);
		break;
	}
	default:
	{
		return nullptr;
	}
	}
}
