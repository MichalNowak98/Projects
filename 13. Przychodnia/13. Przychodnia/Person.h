#pragma once
#include <string>
class Person
{
public:
	std::string PID;
	std::string get_PID()
	{
		return PID;
	}
	// "clear_reservations" jako polimorficzna funkcja dla doktorow i pacjentow? usuniecie rezerwacji z listy pacjenta albo listy lekarza
	virtual void show_data() = 0;
};