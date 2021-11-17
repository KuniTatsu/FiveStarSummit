#pragma once
#include<string>

class CardEvent {

public:
	CardEvent(int ID, int Eventtype, int Statustype, int num, std::string desc, std::string StatusName,
		int ID2, int Eventtype2, int Statustype2, int num2, std::string desc2, std::string StatusName2);
	~CardEvent();

	

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
	std::string StatusName_;

	//******カード用ステータス*****//
	//２つ目の変化するステータス
	int event_type_second_ = 0;
	int status_type_second_ = 0;
	int num_second_ = 0;
	//説明
	std::string desc__second_ = {};
	//変化するステータスの名前
	std::string StatusName_second_;

	void run_Card_Event();

};