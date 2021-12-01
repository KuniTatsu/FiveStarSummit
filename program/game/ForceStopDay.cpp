#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"
#include<string>
#include "ForceStopDay.h"

ForcedStopDay::ForcedStopDay(int Id, int Month, int Day, std::string Desc)
{
	id = Id;
	day = Day;
	month = Month;
	desc = Desc;

}

ForcedStopDay::~ForcedStopDay()
{
}
