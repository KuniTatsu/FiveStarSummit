#include "CharaMenuManager.h"
#include"CharaWindow.h"

CharaMenuManager::CharaMenuManager()
{
	//CharaWakuPos = {x,y,0};

}

CharaMenuManager::~CharaMenuManager()
{
}



void CharaMenuManager::PosReset()
{
	StatusMenuPos.y = 45;

}

void CharaMenuManager::AddList(CharaWindow* cWindow)
{
	charaWindow_.emplace_back(cWindow);
}

