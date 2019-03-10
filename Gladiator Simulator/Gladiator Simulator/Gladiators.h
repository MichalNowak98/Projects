#pragma once
#include "Computing.h"
#include "Gear.h"
enum Equipment {Unussigned, Assigned};
class Gladiator
{
protected:
	int max_health;
	int stamina;
	int dexterity;
	int strength;
	int attack;
	int defence;

	Gear* weapon;
	Gear* shield;
	Equipment rigth_hand;
	Equipment left_hand;

	int adrenaline;

	int max_base_health;
	int base_stamina;
	int base_dexterity;
	int base_strength;
	int base_attack;
	int base_defence;

	unsigned int level;
	unsigned int fame;
	unsigned int asking_price;
public:
	//Gladiator(int _base_health, int _base_stamina, int _base_adrenaline, int _base_dexterity, int _base_strength, int _fame);
	Gladiator(unsigned int _level, unsigned int _fame);
	~Gladiator();
	//void attack(Gladiator &opponent);
	//void skill(/*jakaœ zmienna zeby wybrac skilla*/);	//tablica 4elementowa?
	bool if_dead();
	bool if_opponent_dead(Gladiator &opponent);
	unsigned int calculate_asking_price();

	/*
	void calculate_statistics();
	virtual_void calculate_race_statistics();
	*/

	//virtual void race_skill();
	
	//void add_fame(int _fame);
};

//dwa miecze, bonus do mieczy
class Roman : public Gladiator
{
	int attack_bonus;
public:
	Roman(unsigned int _level, unsigned int _fame);
	//virtual void race_skill();
};

//bonus do w³óczni, wieksza obrona
class Samnite: public Gladiator
{
	int defense_bonus;
public:
	Samnite(unsigned int _level, unsigned int _fame);
};

//uderzenie tarcza, wiecej zycia i sily
class Gaul: public Gladiator
{
	int health_bonus;
	int strength_bonus;
public:
	Gaul(unsigned int _level, unsigned int _fame);
};

//bonus do sztyletu, podciecie sciegien, kontra(podczas ataku przeciwnika)
class Thracian : public Gladiator
{
	int dexterity_bonus;
public:
	Thracian(unsigned int _level, unsigned int _fame);
};

Gladiator* create_gladiator();
//Rudiarius - wolni gladiatorzy