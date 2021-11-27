#include "Character.h"
#include"CharaWindow.h"
#include<time.h>
#include"DxLib.h"
#include"Ability.h"
//
//
//playerdata = new SaveData_t;
//*playerdata = { "プレイヤー",100.0f,100.0f , 10/*1000*/,10, 0,0, 1,1,0,0,0 };

Chara::Chara(std::string name)
{
	//SRand(time(0));
	charadata = new SaveData_t;

	int rangetype = StatusRandom(2, 0);
	int stance = StatusRandom(2, 0);

	int mainStatus[7] = {};
	for (int i = 0; i < 7; ++i) {
		mainStatus[i] = StatusRandom(20, 1);
	}
	//int atk = StatusRandom(20,1);
	//実際は生成時にランダムで値を決める
	*charadata = { name,
					rangetype,stance,
					mainStatus[0],mainStatus[1],mainStatus[2],mainStatus[3],mainStatus[4],mainStatus[5],mainStatus[6],
					0,0,0,0,0,0,0,
					0,0,0,0,
					{} ,
					2 };

	//ステータスウィンドウの作成
	cWindow = new CharaWindow();

}

Chara::~Chara()
{



}

//randomtype:0→基本ステータス以外のもの
//randomtype:1→基本ステータス 20~40をとる
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

