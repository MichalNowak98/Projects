#pragma once
#include <string>
#include <vector>
#include "Patient.h"
class Patient;	//forward declaration. Klasy inkluduj¹ siê nawzajem
struct Hours
{
	std::string hour;
	std::string ID_patient;
	std::string PID_doc;
	std::string date;
	bool reservation;
};
struct Visits
{
	int hours_count;
	std::string date;
	Hours *hours;
};
class Reservations
{
private:
	int visits_count;
	std::string PID_doc;
	Visits *visits;
	friend class FileInfo;
public:
	~Reservations();
	Reservations();

	std::string get_visit_date(int visit_index);
	int get_visits_count();
	int get_visits_hours_count(const int visit_index);
	Hours* get_Hours_adress(int visit_iterator, int hour_index);
	std::string get_visit_hour(const int visit_index, const int hour_index);

	void set_reservation_true(const int visit_index, const int hour_index);
	void set_reservation_false(const int visit_index, const int hour_index);
	void set_patient_PID(const int visit_index, const int hour_index, const std::string PID);

	bool check_reservation(const int visit_index, const int hour_index);
	void fill_patient_reservations(Patient &patient);
};