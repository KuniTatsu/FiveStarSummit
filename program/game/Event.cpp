#include "Event.h"
#include"GameManager.h"

extern GameManager* gManager;


Event::Event(int ID, int Eventtype, int Statustype, int num, std::string desc)
{
	id_ = ID;
	event_type_ = Eventtype;
	status_type_ = Statustype;
	num_ = num;
	desc_ = desc;


}

Event::~Event()
{
}

void Event::run_Event()
{
	//�ǂ̃C�x���g���������邩�͌��܂��Ă���
	//gamemanager��statusset�֐����Ăяo����ok

	gManager->StatusSet(status_type_, num_);


}
