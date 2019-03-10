#pragma once
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include "Doctor.h"
#include "Reservations.h"
void user_interface(Doctor docArr[], std::map<std::string, Reservations*> &schedule, int doc_size, std::set<std::string> &patient_PIDs, std::vector<Patient>& registered_patients);