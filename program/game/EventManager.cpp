#include "EventManager.h"
#include<vector>
#include<string>
#include"DxLib.h"
#include"../library//t2klib.h"
#include"GameManager.h"

extern GameManager* gManager;


void EventManager::loadEvent()
{
	blue_event = t2k::loadCsv("Csv/blueEvent.csv");
	red_event = t2k::loadCsv("Csv/redEvent.csv");
	white_event = t2k::loadCsv("Csv/whiteEvent.csv");

}

int EventManager::setEvent(int eventType)
{


	for (int i = 0; i < 12; ++i) {
		if (i == eventType) {
			return i;

		}
		else {
			continue;
		}
	}


}

void EventManager::DoEvent(int eventID)
{
	if (0 == eventID) {

		//ƒ`[ƒ€‘Sˆõ‚ÌUŒ‚—Í‚ªã‚ª‚é
		gManager->StatusSet(0);

	}
	else if (1 == eventID) {





	}



}
