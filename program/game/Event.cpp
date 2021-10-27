#include "Event.h"
#include"GameManager.h"

extern GameManager* gManager;


Event::Event(int ID, int Eventtype, int Statustype, int num, std::string desc,std::string StatusName)
{
	id_ = ID;
	event_type_ = Eventtype;
	status_type_ = Statustype;
	num_ = num;
	desc_ = desc;
	StatusName_ = StatusName;


}

Event::~Event()
{
}

void Event::run_Status_Event()
{
	//どのイベントが発動するかは決まっている
	//gamemanagerのstatusset関数を呼び出せばok
	//status_type_:どのステータスを変化させるか,num_:変化量
	gManager->StatusSet(status_type_, num_);


}
