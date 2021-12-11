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

	//イベント種別	master管理
	int eventID = 0;

	//日にちの名前
	std::string myDayName = "";
	//日にち
	int myDay = 0;
	//月の名前
	std::string myMonthName = "";
	//月
	int myMonth = 0;

	void Update();

	void Draw();

	

};