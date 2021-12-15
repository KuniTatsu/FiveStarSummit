#pragma once
#include"../library/t2klib.h"

class CharaMenuManager;
class Menu;

class CharaWindow {

public:

	CharaWindow();
	~CharaWindow();

	t2k::Vector3 windowPos = {};
private:
	Menu* enhanceButton = nullptr;
};