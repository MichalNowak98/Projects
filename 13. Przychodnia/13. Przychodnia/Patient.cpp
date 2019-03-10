#include "Patient.h"
int Patient::get_visit_count() { return visit_count; }
Patient::Patient(std::string _PID)
{
	PID = _PID;
}/*
void Patient::add_visit_count()
{
	visit_count++;
}*/
void Patient::sub_visit_count()
{
	visit_count--;
}

void Patient::show_data()
{
	system("cls");
	std::cout << "PID: " << get_PID() << "\nNumber of visits: " << get_visit_count() << "\n\nClick any button to continue";
}

Patient Patient::operator++()
{
	visit_count += 1;
	return *this;
}

Patient Patient::operator++(int)
{
	Patient copy(PID);
	copy.visit_count = visit_count;
	visit_count += 1;
	return copy;
}


