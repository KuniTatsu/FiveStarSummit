#pragma once
#include<list>
#include<vector>
#include<string>

class Event;

//�C�x���g���e��ۑ�����N���X
class EventManager {

public:

	EventManager();

	//std::list<EventManager*>event_;
	/*
	std::vector< std::vector<std::string> > blue_event;
	std::vector< std::vector<std::string> > red_event;
	std::vector< std::vector<std::string> > white_event;
	//std::vector< std::vector<std::string> > extra_event;
	*/

	std::vector< std::vector<std::string> > event_all;
	std::vector<std::vector<Event*> >eventList;




	//�Q�[�����s���Ɉ�x�����ĂԃC�x���g���[�h�֐�
	void loadEvent();
	//DayCell������邽�тɌĂԃC�x���g�Z�b�g�֐�
	int setEvent(int eventType);


	//0���X�e�[�^�X�㏸,
	//1�����C�p�����[�^up,
	//2������\�͊l��
	//3���A�C�e���l��
	//...
	void DoEvent(int eventID,int randomnum);

	int eventdebugID = 0;
private:
	int Random(int rangeMax);






};