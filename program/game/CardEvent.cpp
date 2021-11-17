#include "CardEvent.h"
#include"GameManager.h"

extern GameManager* gManager;

CardEvent::CardEvent(int ID, int Eventtype, int Statustype, int num, std::string desc, std::string StatusName, 
					int ID2, int Eventtype2, int Statustype2, int num2, std::string desc2, std::string StatusName2)
{
	id_ = ID;
	event_type_ = Eventtype;
	status_type_ = Statustype;
	num_ = num;
	desc_ = desc;
	StatusName_ = StatusName;

}

CardEvent::~CardEvent()
{


}

void CardEvent::run_Card_Event()
{


}
