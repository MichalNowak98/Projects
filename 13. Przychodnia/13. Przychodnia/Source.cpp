#include "Source.h"

int main(int argc, char *argv[])
{
	FileInfo *file_info = open_files(argc, argv);
	std::set<std::string> patient_PIDs;
	std::map<std::string, Reservations*> schedule;
	file_info->load_from_binary(schedule, patient_PIDs);
	std::vector<Patient> registered_patients;
	fill_registered_patient_vector(patient_PIDs, registered_patients, schedule);
	int doc_size = 0;
	Doctor *docArr = create_doc_arr(*file_info, doc_size);
	file_info->load_from_doc_data(docArr, schedule);
	user_interface(docArr, schedule, doc_size, patient_PIDs, registered_patients);
	file_info->save_to_binary(docArr, schedule, patient_PIDs);

	patient_PIDs.clear();
	schedule.clear();
	registered_patients.clear();
	delete[] docArr;
	delete file_info;
	return 0;
}
//dodaæ graf do sprawka + wnioski z czym mia³em troudnoœci