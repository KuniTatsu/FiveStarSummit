#pragma once
#include<DxLib.h>
#include<string>

class Event;

//必ず止まる日のクラス
class ForcedStopDay {

public:

	ForcedStopDay(int Id,int Month, int Day,std::string Desc);
	~ForcedStopDay();

	int id = 0;
	int day = 0;
	int month = 0;

	std::string desc = "";




};