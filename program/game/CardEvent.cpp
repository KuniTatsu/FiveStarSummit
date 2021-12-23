#include "CardEvent.h"
#include"GameManager.h"

extern GameManager* gManager;



CardEvent::CardEvent(int id, int eventType, int atk, int def, int magiatk, int magidef, int spd, int mind, int vit,
		std::string desc, int abiType, int abiId, int tension, int itemid, std::string EventMessage, std::string TeachRef)
{
	Id = id;
	Event_type = eventType;

	Atk_Num = atk;
	Def_Num = def;
	MAtk_Num = magiatk;
	MDef_Num = magidef;
	Spd_Num = spd;
	Mind_Num = mind;
	Vit_Num = vit;

	Desc = desc;

	AbilityType = abiType;

	AbilityId = abiId;

	Tension = tension;

	Item_id = itemid;

	eventMessage = EventMessage;
	teachRef = TeachRef;

	AddNameToVector();
}

CardEvent::~CardEvent()
{


}

void CardEvent::run_Card_Event(int passedDay)
{
	if (AbilityType == -1) {
		gManager->StatusSet(Atk_Num, Def_Num, MAtk_Num, MDef_Num, Spd_Num, Mind_Num, Vit_Num,passedDay);
	}
	else {
		gManager->AbilitySet(AbilityType, AbilityId);
	}

}

void CardEvent::AddNameToVector()
{
	if (Atk_Num != 0) {
		changeStatusName.emplace_back("UŒ‚—Í");
		changeStatusValue.emplace_back(Atk_Num);
	}
	if (Def_Num != 0) {
		changeStatusName.emplace_back("–hŒä—Í");
		changeStatusValue.emplace_back(Def_Num);
	}
	if (MAtk_Num != 0) {
		changeStatusName.emplace_back("–‚–@UŒ‚—Í");
		changeStatusValue.emplace_back(MAtk_Num);
	}
	if (MDef_Num != 0) {
		changeStatusName.emplace_back("–‚–@–hŒä—Í");
		changeStatusValue.emplace_back(MDef_Num);
	}
	if (Spd_Num != 0) {
		changeStatusName.emplace_back("‘f‘‚³");
		changeStatusValue.emplace_back(Spd_Num);
	}
	if (Mind_Num != 0) {
		changeStatusName.emplace_back("Œ«‚³");
		changeStatusValue.emplace_back(Mind_Num);
	}
	if (Vit_Num != 0) {
		changeStatusName.emplace_back("‹v—Í");
		changeStatusValue.emplace_back(Vit_Num);
	}

}
