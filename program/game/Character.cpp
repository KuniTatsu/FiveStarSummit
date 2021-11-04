#include "Character.h"
#include"CharaWindow.h"
//
//
//playerdata = new SaveData_t;
//*playerdata = { "プレイヤー",100.0f,100.0f , 10/*1000*/,10, 0,0, 1,1,0,0,0 };

Chara::Chara()
{

	charadata = new SaveData_t;

	//実際は生成時にランダムで値を決める
	*charadata = { "ほげほげ",
					0,0,
					10,20,30,40,50,60,70,
					 0, 0, 0, 0, 0, 0, 0,
					0,0,0,0,
					{} ,
					2 };

	cWindow = new CharaWindow();



}

Chara::~Chara()
{



}
