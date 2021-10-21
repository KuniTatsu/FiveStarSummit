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
	//どのイベントが発動するかは決まっている
	//gamemanagerのstatusset関数を呼び出せばok

	gManager->StatusSet(status_type_, num_);


}
