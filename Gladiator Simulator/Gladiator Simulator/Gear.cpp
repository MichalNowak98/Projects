#include "Gear.h"

Gear::Gear()
{
	switch (type = weapon_type(random_int(0, 6)))
	{
	case Sword:
	{
		slot = One;
		stamina_modificator = 0;
		dexterity_modificator = 5;
		strength_modificator = 0;
		attack_modificator = 10;
		defence_modificator = 5;
		break;
	}
	case Axe:
	{
		slot = One;
		stamina_modificator = 0;
		dexterity_modificator = -5;
		strength_modificator = 10;
		attack_modificator = 5;
		defence_modificator = 0;
		break;
	}
	case Dagger:
	{
		slot = One;
		stamina_modificator = 10;
		dexterity_modificator = 10;
		strength_modificator = -10;
		attack_modificator = 5;
		defence_modificator = -10;
		break;
	}
	case Polearm:
	{
		slot = Two;
		stamina_modificator = -5;
		dexterity_modificator = -5;
		strength_modificator = 5;
		attack_modificator = 0;
		defence_modificator = 10;
		break;
	}
	case Spear_and_net:
	{
		slot = Two;
		stamina_modificator = -5;
		dexterity_modificator = 5;
		strength_modificator = -5;
		attack_modificator = 10;
		defence_modificator = 5;
		break;
	}
	case Light_shield:
	{
		slot = One;
		stamina_modificator = 0;
		dexterity_modificator = -5;
		strength_modificator = -5;
		attack_modificator = -5;
		defence_modificator = 20;
		break;
	}
	case Tower_shield:
	{
		slot = One;
		stamina_modificator = -10;
		dexterity_modificator = -30;
		strength_modificator = -10;
		attack_modificator = -15;
		defence_modificator = 40;
		break;
	}
	}
};

int Gear::get_stamina_modificator() { return stamina_modificator; }

int Gear::get_dexterity_modificator() { return dexterity_modificator; }

int Gear::get_strength_modificator() { return strength_modificator; }

int Gear::get_attack_modificator() { return attack_modificator; }

int Gear::get_defence_modificator() { return defence_modificator; }
