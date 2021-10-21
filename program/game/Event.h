#pragma once
#include<string>

class Event {

public:
	Event(int ID, int Eventtype, int Statustype, int num, std::string desc);
	~Event();

	int id_ = 0;
	int event_type_ = 0;
	int status_type_ = 0;
	int num_ = 0;
	std::string desc_ = {};


	void run_Event();

};