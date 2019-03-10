#pragma once
#include<iostream>
#include "Person.h"
#include <String>
class Doctor : public Person
{
	friend class FileInfo;
protected:
	std::string first_name;
	std::string last_name;
	std::string specialization;
	std::string days_and_hours;
public:
	void fill_days_and_hours(std::string &buffer);
	bool doc_match(std::string const _first_name, std::string const _last_name);
	bool spec_match(std::string const _spec);
	void show_data();
};