#include "Interface.h"
void show_data(Person &person)
{
	person.show_data();
}
std::string find_doctor(Doctor docArr[], std::string first_name, std::string last_name, const int doc_size)
{
	for (int i = 0; i < doc_size; i++)
	{
		if (docArr[i].doc_match(first_name, last_name))
			return docArr[i].get_PID();
	}
	return "no_doc";
}
std::vector<std::string> find_spec(std::vector<std::string> PIDs, Doctor docArr[], const std::string spec, const int doc_size)
{
	for (int i = 0; i < doc_size; i++)
	{
		if (docArr[i].spec_match(spec))
			PIDs.push_back(docArr[i].get_PID());
	}
	return PIDs;
}
int choose_day(std::map<std::string, Reservations*> &schedule, const std::string PID_doc)
{
	system("cls");
	for (int visit_iterator = 0; visit_iterator < schedule[PID_doc]->get_visits_count(); visit_iterator++)
	{
		std::cout << visit_iterator + 1 << ". " << schedule[PID_doc]->get_visit_date(visit_iterator) << std::endl;
	}
	std::cout << "Choose day: ";
	//zapewnienie poprawnego wyboru
	int visit_index = -1;
	while (visit_index < 0 || visit_index >= schedule[PID_doc]->get_visits_count())
	{
		std::cin >> visit_index;
		if (visit_index == 0)
			return -1;
		visit_index--;
		if (visit_index < 0 || visit_index >= schedule[PID_doc]->get_visits_count())
			std::cout << "Choose correct number (\"1\"): ";
	}
	return visit_index;
}
int choose_hour(std::map<std::string, Reservations*> &schedule, const std::string PID_doc, const int visit_index, const std::string PID, int &patients_index, std::vector<Patient>& registered_patients)
{
	system("cls");
	for (int hour_iterator = 0; hour_iterator < schedule[PID_doc]->get_visits_hours_count(visit_index); hour_iterator++)
	{
		std::cout << hour_iterator + 1 << ". " << schedule[PID_doc]->get_visit_hour(visit_index, hour_iterator) << std::endl;
	}
	//zapewnienie poprawnego wyboru, jeœli istnieje rezerwacja trzeba dokonac kolejnego wyboru
	int hour_index = -1;
	while (hour_index < 0 || hour_index >= schedule[PID_doc]->get_visits_hours_count(visit_index) || schedule[PID_doc]->check_reservation(visit_index, hour_index))
	{
		std::cin >> hour_index;
		if (hour_index == 0)
			return -1;
		hour_index--;
		if (hour_index < 0 || hour_index >= schedule[PID_doc]->get_visits_hours_count(visit_index) || schedule[PID_doc]->check_reservation(visit_index, hour_index))
			std::cout << "Choose correct and not RESERVED number (\"1\"): ";
	}
	schedule[PID_doc]->set_reservation_true(visit_index, hour_index);
	schedule[PID_doc]->set_patient_PID(visit_index, hour_index, PID);
	registered_patients[patients_index].visits.push_back(schedule[PID_doc]->get_Hours_adress(visit_index, hour_index));
	registered_patients[patients_index]++;;
	return hour_index;
}
void user_interface(Doctor docArr[], std::map<std::string, Reservations*> &schedule, int doc_size, std::set<std::string> &patient_PIDs, std::vector<Patient>& registered_patients)
{
	char choice;
	int visit_index = -1, hour_index;
	bool loop = true;
	std::string first_name, last_name, spec, element_doc, curr_PID;
	std::cout << "Write your ID:";
	std::cin >> curr_PID;
	if (!(patient_PIDs.find(curr_PID) != patient_PIDs.end()))
	{
		patient_PIDs.insert(curr_PID);
		Patient *_patient = new Patient(curr_PID);
		registered_patients.push_back(*_patient);
	}
	int current_patient_index = 0;
	while (current_patient_index < registered_patients.size() && registered_patients[current_patient_index].PID != curr_PID)
	{
		current_patient_index++;
	}
	while (loop == true)
	{
		system("cls");
		std::cout << "1. Find doctor\n2. Find specialisation\n3. Check your reservations\n4. Show your data\n5. Show doctor data\n0. Quit\n";
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		case '1':
		{
			visit_index = -1;
			hour_index = -1;
			while (visit_index == -1)
			{
			system("cls");
			std::cout << "First name: (0 to quit)";
			std::cin >> first_name;
			if (first_name == "0")
			{
				break;
			}
			std::cout << "Last name: ";
			std::cin >> last_name;	
			element_doc = find_doctor(docArr, first_name, last_name, doc_size);
			hour_index = -1;
			if (element_doc == "no_doc")
			{
				std::cout << "There is no such doctor.";
				system("pause>nil");
				break;
			}
			while (hour_index == -1)
			{
				visit_index = choose_day(schedule, element_doc);
				if (visit_index != -1)
					hour_index = choose_hour(schedule, element_doc, visit_index, curr_PID, current_patient_index, registered_patients);
				else
					hour_index = 0; //wyjœcie z pêtli
			}
			}
			break;
		}
		case '2':
		{
			visit_index = -1;
			hour_index = -1;
			while (visit_index == -1)
			{
				system("cls");
				std::cout << "Specialization: (0 to quit)";
				std::cin >> spec;
				if (spec == "0")
				{
					break;
				}
				std::vector<std::string> PIDs = find_spec(PIDs, docArr, spec, doc_size);
				if (PIDs.size() == 0)
				{
					std::cout << "There is no such specialization.";
					system("pause>nil");
					break;
				}
				hour_index = -1;
				system("cls");

				while (hour_index == -1)
				{
					std::cout << "Choose number of doctor with date: \n";
					for (int PIDs_iterator = 0; PIDs_iterator < PIDs.size(); PIDs_iterator++)
					{
						std::cout << PIDs_iterator + 1 << ". ";
						for (int visit_iterator = 0; visit_iterator < schedule[PIDs[PIDs_iterator]]->get_visits_count(); visit_iterator++)
						{
							std::cout << schedule[PIDs[PIDs_iterator]]->get_visit_date(visit_iterator) << std::endl;
						}
					}
					int PIDs_index = 0;
					std::cin >> PIDs_index;
					PIDs_index--;
					if (PIDs_index >= PIDs.size() || PIDs_index < 0)
					{
						std::cout << "Out of range";
						break;
					}
					visit_index = choose_day(schedule, PIDs[PIDs_index]);
					if (visit_index != -1)
						hour_index = choose_hour(schedule, PIDs[PIDs_index], visit_index, curr_PID, PIDs_index, registered_patients);
					else
						hour_index = 0; //wyjœcie z pêtli
				}
			}
			break;
		}
		case '3':
		{
			for (int i = 0; i < registered_patients[current_patient_index].get_visit_count(); i++)
			{
				std::cout << i + 1 << ". " << registered_patients[current_patient_index].visits[i]->date << " " << registered_patients[current_patient_index].visits[i]->hour << "\n";
			}
			std::cout << "1. Cancel visit\n0. Go back.\n";
			std::cin >> choice;
			switch (choice)
			{
			case '0':
			{
				break;
			}
			case '1':
			{
				std::cout << "Which date should be canceled? (writing number out of range will abort canceling)\n";
				int chosen_date;
				std::cin >> chosen_date;
				if (chosen_date > 0 && chosen_date <= registered_patients[current_patient_index].visits.size())
				{
					registered_patients[current_patient_index].visits[chosen_date - 1]->ID_patient = "";
					registered_patients[current_patient_index].visits[chosen_date - 1]->reservation = false;
					registered_patients[current_patient_index].visits.erase(registered_patients[current_patient_index].visits.begin() + chosen_date - 1);
					registered_patients[current_patient_index].sub_visit_count();
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case '4':
		{
			show_data(registered_patients[current_patient_index]);
			system("pause>nil");
			break;
		}
		case '5':
		{
			system("cls");
			for (int i = 0; i < doc_size; i++)
			{
				show_data(docArr[i]);
				std::cout << "\n\n";
			}
			std::cout << "Click any button to continue";
			system("pause>nil");
			break;
		}
		case '0':
		{
			loop = false;
			break;
		}
		default:
			break;
		}

	}
}