#pragma once
#include<string>

class Event {

public:
	Event(int ID, int Eventtype, int Statustype, int num, std::string desc,std::string StatusName);
	~Event();

	Event(int ID, int Eventtype, int Statustype, int num, std::string desc, std::string StatusName,
		int ID2, int Eventtype2, int Statustype2, int num2, std::string desc2, std::string StatusName2);

	//eventID
	int id_ = 0;
	//0,1,2...master参照
	int event_type_ = 0;
	//変化するステータス
	int status_type_ = 0;
	//変化量
	int num_ = 0;
	//説明
	std::string desc_ = {};
	//変化するステータスの名前
	std::string StatusName_ ;

	


	void run_Status_Event();

};