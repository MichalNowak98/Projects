#pragma once
#include <iostream>
#include"Person.h"
#include "Reservations.h"
#include <vector>
struct Hours;
class Patient : public Person
{
private:
	int visit_count;
public:
	std::vector<Hours*> visits;

	Patient(std::string _PID);
	int get_visit_count();
	//void add_visit_count();
	void sub_visit_count();
	void show_data();
	Patient operator++();
	Patient operator++(int);
};