#pragma once
#include"Computing.h"
enum weapon_type {Sword, Axe, Dagger, Polearm, Spear_and_net, Light_shield, Tower_shield};
enum slot_amount {One, Two};
class Gear
{
	weapon_type type;
	slot_amount slot;

	int stamina_modificator;
	int dexterity_modificator;
	int strength_modificator;
	int attack_modificator;
	int defence_modificator;
public:
	Gear();
	int get_stamina_modificator();
	int get_dexterity_modificator();
	int get_strength_modificator();
	int get_attack_modificator();
	int get_defence_modificator();
};