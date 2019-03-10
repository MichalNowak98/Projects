#include "Doctor.h"
void Doctor::fill_days_and_hours(std::string &buffer)
{
	for (int i = 0; buffer[i] != ';'; i++)
	{
		days_and_hours += buffer[i];
	}
}
bool Doctor::doc_match(std::string const _first_name, std::string const _last_name)
{
	if (first_name == _first_name && last_name == _last_name)
		return true;
	else
		return false;
}
bool Doctor::spec_match(std::string const spec)
{
	if (specialization == spec)
		return true;
	else
		return false;
}
void Doctor::show_data()
{
	std::cout << "PID: " << get_PID() << "\nFirst name: " << first_name << "\nLast name: " << last_name << "\nSpecialization: " << specialization << "\nVisits: " << days_and_hours;
}