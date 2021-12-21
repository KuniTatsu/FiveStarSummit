#pragma once
#include"../library/t2klib.h"

class CharaMenuManager;
class Menu;

class CharaWindow {

public:

	CharaWindow();
	~CharaWindow();

	//window©g‚Ì•`‰æÀ•W(CharaMenuManager‚ÌStatusMenuPos‚ÉˆË‘¶‚³‚¹‚é
	t2k::Vector3 windowPos = {};
private:
	Menu* enhanceButton = nullptr;
};