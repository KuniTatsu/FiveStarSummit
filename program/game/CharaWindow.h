#pragma once
#include"../library/t2klib.h"

class CharaMenuManager;
class Menu;

class CharaWindow {

public:

	CharaWindow();
	~CharaWindow();

	//window自身の描画座標(CharaMenuManagerのStatusMenuPosに依存させる
	t2k::Vector3 windowPos = {};
private:
	Menu* enhanceButton = nullptr;
};