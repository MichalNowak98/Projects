#include "FileInfo.h"
FileInfo::FileInfo() : in("database.bin"), out("database.bin"), indoc("doctor_data.txt"), lines(0)
{
	file_in.open(in, std::ios::binary);
	file_doc.open(indoc);
};
FileInfo::FileInfo(std::string _out) : in("database.bin"), out(_out), indoc("doctor_data.txt"), lines(0)
{
	file_in.open(in, std::ios::binary);
	file_doc.open(indoc);
};
FileInfo::FileInfo(std::string _out, std::string _indoc) : in("database.bin"), out(_out), indoc(_indoc), lines(0)
{
	file_in.open(in, std::ios::binary);
	file_doc.open(indoc);
};
FileInfo::FileInfo(std::string _out, std::string _indoc, std::string _in) : in(_in), out(_out), indoc(_indoc), lines(0)
{
	file_in.open(in, std::ios::binary);
	file_doc.open(indoc);
};
FileInfo::~FileInfo()
{
	file_doc.close();
	file_in.close();
	file_out.close();
};
void get_word(std::string &buffer, std::string &data)
{
	while (buffer[0] != ',')
	{
		data += buffer[0];
		buffer.erase(0, 1);
	}
	//delete ", "
	buffer.erase(0, 2);
}
int FileInfo::count_lines_and_save_to_buffer_string()
{
	//lines = 0;
	std::string line;
	while (std::getline(file_doc, line))
	{
		++lines;
		buffer += line;
		buffer += ";";
	}
	return lines;
}
void FileInfo::load_from_doc_data(Doctor docArr[], std::map<std::string, Reservations*> &schedule)
{
	std::string time_buffer;
	int hours[2], minutes[2];
	for (int i = 0; i < lines; i++)
	{
	Reservations *_reservation = new Reservations;
		get_word(buffer, (docArr[i]).PID);
		_reservation->PID_doc = docArr[i].PID;
		get_word(buffer, (docArr[i]).first_name);
		get_word(buffer, (docArr[i]).last_name);
		get_word(buffer, (docArr[i]).specialization);
		docArr[i].fill_days_and_hours(buffer);
		int count = 1;
		//count - liczba dni, w których doktor przyjmuje
		for (int j = 0; buffer[j] != ';'; j++)
		{
			if (buffer[j] == ',')
				count++;
		}
		_reservation->visits = new Visits[count];
		_reservation->visits_count = count;
		for (int j = 0; j < count; j++)
		{
			while (buffer[0] != ' ')
			{
				_reservation->visits[j].date += buffer[0];
				buffer.erase(0, 1);
			}
			buffer.erase(0, 1);
			while (buffer[0] != ':')
			{
				time_buffer += buffer[0];
				buffer.erase(0, 1);
			}
			buffer.erase(0, 1);
			hours[0] = std::stoi(time_buffer);
			time_buffer = "";
			while (buffer[0] != '-')
			{
				time_buffer += buffer[0];
				buffer.erase(0, 1);
			}
			buffer.erase(0, 1);
			minutes[0] = std::stoi(time_buffer);
			time_buffer = "";
			while (buffer[0] != ':')
			{
				time_buffer += buffer[0];
				buffer.erase(0, 1);
			}
			buffer.erase(0, 1);
			hours[1] = std::stoi(time_buffer);
			time_buffer = "";
			while (buffer[0] != ',' && buffer[0] != ';')
			{
				time_buffer += buffer[0];
				buffer.erase(0, 1);
			}
			minutes[1] = std::stoi(time_buffer);
			time_buffer = "";
			if (buffer[0] == ';')
				buffer.erase(0, 1);
			else
				buffer.erase(0, 2);
			//zak³adaj¹c ¿e s¹ tylko godziny X:00 - Y:00
			int visits_number = (hours[1] - hours[0]) * 4;
			_reservation->visits[j].hours = new Hours[visits_number];
			_reservation->visits[j].hours_count = visits_number;
			for (int k = 0; k < visits_number; k++)
			{
				_reservation->visits[j].hours[k].reservation = false;
				_reservation->visits[j].hours[k].hour = std::to_string(hours[0]) + ":" + std::to_string(minutes[0]);
				if (minutes[0] == 0)
					_reservation->visits[j].hours[k].hour += "0";
				minutes[0] += 15;
				if (minutes[0] == 60)
				{
					minutes[0] = 0;
					hours[0]++;
				}
				_reservation->visits[j].hours[k].PID_doc = docArr[i].PID;
				_reservation->visits[j].hours[k].date = _reservation->visits[j].date;
			}
		}
		schedule.insert(std::pair<std::string, Reservations*>(_reservation->PID_doc, _reservation));
	}
}
void FileInfo::load_from_binary(std::map<std::string, Reservations*> &schedule, std::set<std::string> &patient_PIDs)
{
	if (file_in.peek() != std::ifstream::traits_type::eof())
	{
		int patient_size = 0;
		file_in.read((char*)&patient_size, sizeof(patient_size));
		for (int i = 0; i < patient_size; i++)
		{
			std::string _PID;
			_PID.resize(11); //znak konca lini jest ignorowany, daltego 11 a nie 12
			file_in.read((char*)_PID.c_str(), 11);
			patient_PIDs.insert(_PID);
		}
	}
	while (file_in.peek() != std::ifstream::traits_type::eof())
	{
		std::string _PID;
		Reservations *_res = new Reservations;
		_PID.resize(11);
		file_in.read((char*)_PID.c_str(), 11);
		int size_res = 0, count_visits = 0, count_hours = 0;
		file_in.read((char*)&size_res, sizeof(size_res));
		file_in.read((char*)&(*_res), size_res);
		file_in.read((char*)&count_visits, sizeof(count_visits));
		_res->visits = new Visits[count_visits];
		for (int j = 0; j < count_visits; j++)
		{
			file_in.read((char*)&(_res->visits[j]), sizeof(Visits));
			file_in.read((char*)&count_hours, sizeof(count_hours));
			_res->visits[j].hours = new Hours[count_hours];
			for (int k = 0; k < count_hours; k++)
			{
				file_in.read((char*)&_res->visits[j].hours[k], sizeof(Hours));
			}
		}
		schedule.insert(std::pair<std::string, Reservations*>(_PID, _res));
	}	
}
//pesel - rozmiar sruktury - struktura -  liczba wizyt (int) - (wizyta - ilosc godzin - (godzina))
void FileInfo::save_to_binary(Doctor docArr[], std::map<std::string, Reservations*> &schedule, std::set<std::string> &patient_PIDs)
{
	file_out.open(out, std::ios::binary);
	int patient_size = patient_PIDs.size();
	file_out.write((char*)&patient_size, sizeof(int));
	if (patient_PIDs.size() != 0)
	{
		std::set<std::string>::iterator curr_el;
		for (curr_el = patient_PIDs.begin(); curr_el != patient_PIDs.end(); curr_el++)
		{
			std::string _PID = *curr_el;
			file_out.write((char*)_PID.c_str(), 11);
		}
	}
	for (int i = 0; i < schedule.size(); i++)
	{
		std::string _PID = docArr[i].get_PID();
		int size_res = sizeof((*schedule[_PID])), count_visits = schedule[_PID]->get_visits_count(), count_hours = 0;
		file_out.write((char*)_PID.c_str(), 11);
		file_out.write((char*)&size_res, sizeof(size_res));
		file_out.write((char*)&(*schedule[_PID]), size_res);
		file_out.write((char*)&count_visits, sizeof(count_visits));
		for (int j = 0; j < count_visits; j++)
		{
			file_out.write((char*)&schedule[_PID]->visits[j], sizeof(Visits));
			count_hours = schedule[_PID]->visits[j].hours_count;
			file_out.write((char*)&count_hours, sizeof(count_hours));
			for (int k = 0; k < count_hours; k++)
			{
				file_out.write((char*)&schedule[_PID]->visits[j].hours[k], sizeof(Hours));
			}
		}
	}
}
