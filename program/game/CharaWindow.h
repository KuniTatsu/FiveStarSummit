#pragma once
#include"../library/t2klib.h"

class CharaMenuManager;
class Menu;

class CharaWindow {

public:

	CharaWindow();
	~CharaWindow();

	//window���g�̕`����W(CharaMenuManager��StatusMenuPos�Ɉˑ�������
	t2k::Vector3 windowPos = {};
private:
	Menu* enhanceButton = nullptr;
};