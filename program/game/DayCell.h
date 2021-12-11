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

	//�C�x���g���	master�Ǘ�
	int eventID = 0;

	//���ɂ��̖��O
	std::string myDayName = "";
	//���ɂ�
	int myDay = 0;
	//���̖��O
	std::string myMonthName = "";
	//��
	int myMonth = 0;

	void Update();

	void Draw();

	

};