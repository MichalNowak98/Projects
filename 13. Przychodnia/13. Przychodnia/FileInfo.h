#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Doctor.h"
#include "Reservations.h"
#include <set>
#include <map>
class FileInfo
{
	std::ifstream file_doc;
	std::ifstream file_in;
	std::ofstream file_out;
	std::string in;
	std::string out;
	std::string indoc;
	std::string buffer;
	int lines;
public:
	FileInfo();
	FileInfo(std::string _out);
	FileInfo(std::string _out, std::string _indoc);
	FileInfo(std::string _out, std::string _indoc, std::string _in);
	~FileInfo();
	int count_lines_and_save_to_buffer_string();
	void load_from_doc_data(Doctor docArr[], std::map<std::string, Reservations*> &schedule);
	void load_from_binary(std::map<std::string, Reservations*> &schedule, std::set<std::string> &patient_PIDs);
	void save_to_binary(Doctor docArr[], std::map<std::string, Reservations*> &schedule, std::set<std::string> &patient_PIDs);
};