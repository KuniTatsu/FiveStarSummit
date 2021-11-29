#pragma once
#include"../library/t2klib.h"
#include <string>
#include<unordered_map>


class DayCell {

public:
	DayCell(int cell_gh);
	~DayCell();

	t2k::Vector3 pos_;



	int gh = 0;
	bool is_alive_ = true;

	//0,1,2から選ばれる
	int eventID = 0;

	std::string myDayName = "";

	int myDay = 0;
	std::string myMonthName = "";

	void Update();

	void Draw();

	

};