#include "Character.h"
#include"CharaWindow.h"
#include<time.h>
#include"DxLib.h"
#include"Ability.h"
#include"MenuWindow.h"

std::string Chara::trainingAll[Chara::MENU_MAX] = {
		"Random",
		"ATACK",
		"DEFENCE",
		"MAGIARACK",
		"MAGIDEFENCE",
		"SPEED",
		"MIND",
		"VITALITY",
};
//
//
//playerdata = new SaveData_t;
//*playerdata = { "�v���C���[",100.0f,100.0f , 10/*1000*/,10, 0,0, 1,1,0,0,0 };

Chara::Chara(std::string name, int year)
{
	//SRand(time(0));
	charadata = new SaveData_t;

	//�������Ƀ����_���Œl�����߂�
	int rangetype = StatusRandom(2, 0);
	int stance = StatusRandom(2, 0);

	int mainStatus[7] = {};
	for (int i = 0; i < 7; ++i) {
		mainStatus[i] = StatusRandom(20, 1);
	}
	//int atk = StatusRandom(20,1);
	*charadata = { name,
					rangetype,stance,
					mainStatus[0],mainStatus[1],mainStatus[2],mainStatus[3],mainStatus[4],mainStatus[5],mainStatus[6],
					0,0,0,0,0,0,0,
					0,0,0,0,
					{} ,
					2 ,
					Chara::trainingAll[Chara::Random],
					year
	};

	
	
	//�X�e�[�^�X�E�B���h�E�̍쐬
	cWindow = new CharaWindow();
	//charaListWindow = new Menu(cWindow->windowPos.x - (600 / 2), cWindow->windowPos.y, 600, 250, "graphics/WindowBase_02.png");
	charaListWindow = new Menu(0, 0, 600, 250, "graphics/WindowBase_02.png");
	charaEnhanceWindow = new Menu(0, 0, 600, 250, "graphics/WindowBase_02.png");
	enhanceButton = new Menu(0, 0, 140, 50, "graphics/WindowBase_02.png");

}

Chara::~Chara()
{



}

void Chara::changeWindowPos(int x, int y, int type)
{
	//charaListWindow�𓮂���
	if (type == 0) {
		charaListWindow->menu_x = x;
		charaListWindow->menu_y = y;
	}
	//charaEnhanceWindow�𓮂���
	else if (type == 1) {
		charaEnhanceWindow->menu_x = x;
		charaEnhanceWindow->menu_y = y;
	}
}

//randomtype:0����{�X�e�[�^�X�ȊO�̂���
//randomtype:1����{�X�e�[�^�X 20~40���Ƃ�
int Chara::StatusRandom(int maxnum, int randomtype)
{
	int random = 0;
	if (randomtype == 0) {
		random = GetRand(maxnum);
	}
	else {
		random = GetRand(maxnum) + 20;//0~20+20
	}
	return random;
}

