#include "Character.h"
#include"CharaWindow.h"
#include<time.h>
#include"DxLib.h"
#include"Ability.h"
#include"MenuWindow.h"

std::string Chara::trainingAll[Chara::MENU_MAX] = {
		"おまかせ",
		"攻撃力",
		"防御力",
		"魔法攻撃力",
		"魔法防御力",
		"素早さ",
		"賢さ",
		"持久力",
};
//
//
//playerdata = new SaveData_t;
//*playerdata = { "プレイヤー",100.0f,100.0f , 10/*1000*/,10, 0,0, 1,1,0,0,0 };

Chara::Chara(std::string name, int year)
{
	//SRand(time(0));
	charadata = new SaveData_t;

	//生成時にランダムで値を決める
	int rangetype = StatusRandom(2, 0, year);
	int stance = StatusRandom(2, 0, year);

	int mainStatus[7] = {};
	for (int i = 0; i < 7; ++i) {
		mainStatus[i] = StatusRandom(20, 1, year);
	}
	//int atk = StatusRandom(20,1);
	*charadata = { name,
					rangetype,stance,
					mainStatus[0],mainStatus[1],mainStatus[2],mainStatus[3],mainStatus[4],mainStatus[5],mainStatus[6],
					0,0,0,0,0,0,0,
					0,0,0,0,
					{} ,
					2 ,
					Chara::trainingAll[Chara::おまかせ],
					year
	};



	//ステータスウィンドウの作成
	cWindow = new CharaWindow();
	//charaListWindow = new Menu(cWindow->windowPos.x - (600 / 2), cWindow->windowPos.y, 600, 250, "graphics/WindowBase_02.png");
	charaListWindow = new Menu(0, 0, 600, 250, "graphics/WindowBase_02.png");
	charaEnhanceWindow = new Menu(0, 0, 620, 100, "graphics/WindowBase_02.png");
	enhanceButton = new Menu(0, 0, 165, 50, "graphics/WindowBase_02.png");

}

Chara::~Chara()
{



}

void Chara::changeWindowPos(int x, int y, int type)
{
	//charaListWindowを動かす
	if (type == 0) {
		charaListWindow->menu_x = x;
		charaListWindow->menu_y = y;
	}
	//charaEnhanceWindowを動かす
	else if (type == 1) {
		charaEnhanceWindow->menu_x = x;
		charaEnhanceWindow->menu_y = y;
	}
}

//randomtype:0→基本ステータス以外のもの
//randomtype:1→基本ステータス 20~40をとる
int Chara::StatusRandom(int maxnum, int randomtype, int year)
{
	int random = 0;
	if (randomtype == 0) {
		random = GetRand(maxnum);
	}
	else {
		//学年ごとに初期ステータスを変化させる
		//学年*5~25を足す 最大初期ステータスは40+50=90
		random = GetRand(maxnum) + 20 + ((year - 1) * ((GetRand(4) + 1) * 5));
	}
	return random;
}

