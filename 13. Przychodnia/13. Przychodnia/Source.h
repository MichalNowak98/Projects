#pragma once
#include <iostream>
#include <String>
#include <fstream>
#include "Doctor.h"
#include "FileInfo.h"
#include "Interface.h"
#include "Reservations.h"
#include "Patient.h"
#include "Source.h"
FileInfo* open_files(int argc, char *argv[])
{
	system("cls");
	if (argc == 1)
	{
		return new FileInfo();
	}
	if (argc == 2)
	{
		return new FileInfo(argv[1]);
	}
	if (argc == 3)
	{
		return new FileInfo(argv[1], argv[2]);
	}
	if (argc == 4)
	{
		return new FileInfo(argv[1], argv[2], argv[3]);
	}
}
Doctor* create_doc_arr(FileInfo &file_info, int &doc_size)
{
	doc_size = file_info.count_lines_and_save_to_buffer_string();
	Doctor *docArr = new Doctor[doc_size];
	return docArr;
}
void fill_registered_patient_vector(std::set<std::string> &patient_PIDs, std::vector<Patient> &registered_patients, std::map<std::string, Reservations*> &reservations)
{
	std::set<std::string>::iterator curr_set_el;
	for (curr_set_el = patient_PIDs.begin(); curr_set_el != patient_PIDs.end(); curr_set_el++)
	{
		Patient *patient = new Patient(*curr_set_el);
		//dla pojedynczego pacjenta petla przypisuje rezerwacje od kazdego lekarza po kolei
		for (std::map<std::string, Reservations*>::iterator curr_map_el = reservations.begin(); curr_map_el != reservations.end(); curr_map_el++)
		{
			curr_map_el->second->fill_patient_reservations(*patient);
		}
		registered_patients.push_back(*patient);
	}
}