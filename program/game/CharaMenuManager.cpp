#include "CharaMenuManager.h"
#include"CharaWindow.h"

CharaMenuManager::CharaMenuManager()
{
	//CharaWakuPos = {x,y,0};

}

CharaMenuManager::~CharaMenuManager()
{
}

void CharaMenuManager::DrawWindow()
{

	int i = 0;
	for (auto cWindow : charaWindow_) {
		cWindow->windowPos.x = StatusMenuPos.x;
		cWindow->windowPos.y = StatusMenuPos.y + (20 * (i+1)) + ((CharaWindowHeight) * (i));
		i++;
		DrawBox(cWindow->windowPos.x - (CharaWindowWidth / 2), cWindow->windowPos.y,
			cWindow->windowPos.x + (CharaWindowWidth / 2), cWindow->windowPos.y + CharaWindowHeight, -1, true);
	}

}

void CharaMenuManager::AddList(CharaWindow* cWindow)
{
	charaWindow_.emplace_back(cWindow);
}

