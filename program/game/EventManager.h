#pragma once
#include<list>
#include<vector>
#include<string>

//�C�x���g���e��ۑ�����N���X
class EventManager {

public:

	//std::list<EventManager*>event_;
	std::vector< std::vector<std::string> > blue_event;
	std::vector< std::vector<std::string> > red_event;
	std::vector< std::vector<std::string> > white_event;
	//std::vector< std::vector<std::string> > extra_event;

	//�Q�[�����s���Ɉ�x�����ĂԃC�x���g���[�h�֐�
	void loadEvent();
	//DayCell������邽�тɌĂԃC�x���g�Z�b�g�֐�
	int setEvent(int eventType);

	void DoEvent(int eventID);



};