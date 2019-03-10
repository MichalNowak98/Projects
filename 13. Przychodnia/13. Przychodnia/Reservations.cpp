#include "Reservations.h"
Reservations::~Reservations()
{
	if (visits != nullptr)
	{
		for (int i = 0; i < visits_count; i++)
		{
			delete[] visits[i].hours;
		}
		delete[] visits;
	}
};
Reservations::Reservations() :visits_count(0), visits(nullptr) {};

std::string Reservations::get_visit_date(int visit_index) 
{ 
	return visits[visit_index].date; 
}
int Reservations::get_visits_count() 
{ 
	return visits_count; 
}
int Reservations::get_visits_hours_count(const int visit_index) 
{
	return visits[visit_index].hours_count;
}
Hours * Reservations::get_Hours_adress(int visit_index, int hour_index) 
{ 
	return &(visits[visit_index].hours[hour_index]); 
}
std::string Reservations::get_visit_hour(const int visit_index, const int hour_index)
{
	if (visits[visit_index].hours[hour_index].reservation == true)
		return visits[visit_index].hours[hour_index].hour + " - RESERVED";
	return visits[visit_index].hours[hour_index].hour;
}

void Reservations::set_reservation_true(const int visit_index, const int hour_index)
{
	visits[visit_index].hours[hour_index].reservation = true;
}
void Reservations::set_reservation_false(const int visit_index, const int hour_index)
{
	visits[visit_index].hours[hour_index].reservation = false;
}
void Reservations::set_patient_PID(const int visit_index, const int hour_index, const std::string PID)
{
	visits[visit_index].hours[hour_index].ID_patient = PID;
}

bool Reservations::check_reservation(const int visit_index, const int hour_index)
{
	return visits[visit_index].hours[hour_index].reservation;
}
void Reservations::fill_patient_reservations(Patient &patient)
{
	for (int visit_iterator = 0; visit_iterator < visits_count; visit_iterator++)
	{
		for (int hours_iterator = 0; hours_iterator < visits[visit_iterator].hours_count; hours_iterator++)
		{
			if (visits[visit_iterator].hours[hours_iterator].reservation == true && visits[visit_iterator].hours[hours_iterator].ID_patient == patient.PID)
			{
				patient++;	//zwiekszenie liczby wizyt o jeden za pomoca operatora ++
				patient.visits.push_back(&(visits[visit_iterator].hours[hours_iterator]));
			}
		}
	}
}
