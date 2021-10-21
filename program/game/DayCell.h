#pragma once
#include"../library/t2klib.h"


class DayCell {

public:
	DayCell(int cell_gh);
	~DayCell();

	t2k::Vector3 pos_;

	int gh = 0;
	bool is_alive_ = true;

	int eventID = 0;

	void Update();

	void Draw();

};