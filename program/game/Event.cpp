#include "Event.h"
#include"GameManager.h"

extern GameManager* gManager;


Event::Event(int ID, int Eventtype, int Statustype, int num, std::string desc,std::string StatusName, std::string EventName, std::string EventMessage)
{
	id_ = ID;
	event_type_ = Eventtype;
	status_type_ = Statustype;
	num_ = num;
	desc_ = desc;
	statusName = StatusName;
	eventName = EventName;
	eventMessage = EventMessage;

}

Event::~Event()
{
}

void Event::run_Status_Event()
{
	//�ǂ̃C�x���g���������邩�͌��܂��Ă���
	//gamemanager��statusset�֐����Ăяo����ok
	//status_type_:�ǂ̃X�e�[�^�X��ω������邩,num_:�ω���
	gManager->StatusSet(status_type_, num_);


}
