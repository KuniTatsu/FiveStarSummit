#include "Item.h"
#include"CharaWindow.h"
#include "GameManager.h"
#include"MenuWindow.h"

extern GameManager* gManager;

Item::Item(int Id, int ItemType, int SetDay, int AddStatusType, int AddStatusNum, int SetAbilityId,
	int SetAbilityType, std::string Gh, std::string Desc, std::string Name, int Num)
{
	id = Id;
	itemType = ItemType;
	setDay = SetDay;
	addStatusType = AddStatusType;
	addStatusNum = AddStatusNum;
	setAbilityId = SetAbilityId;
	setAbilityType = SetAbilityType;
	gh_pass = Gh;
	desc = Desc;
	name = Name;
	button = new Menu(0, 0, 70, 45, "graphics/WindowBase_02.png");
	frame = new Menu(0, 0, 600, 50, "graphics/WindowBase_02.png");
	num = Num;
	gh = gManager->LoadGraphEx(gh_pass);
}

Item::~Item()
{
}
