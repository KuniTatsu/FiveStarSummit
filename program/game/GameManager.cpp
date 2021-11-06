#include "GameManager.h"
#include"SceneManager.h"
#include"Character.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"
#include<string>



GameManager::GameManager()
{
	//sManager = new SceneManager();
	deitatime_ = 0;
	SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);
}

GameManager::~GameManager()
{
}

void GameManager::MakeCharacter()
{

	InputName();
	
	//string型に変換
	std::string name(String, sizeof(String) / sizeof(String[0]));
	isInput = false;

	chara_ = new Chara(name);
	chara.emplace_back(chara_);
}

void GameManager::InputName()
{
	isInput = true;

	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);


	//入力を始めたいところで
	SetActiveKeyInput(InputHandle);

	//以降の入力はすべてInputHandleに行く

	while (!ProcessMessage()) {

		//文字入力が終了しているならwhileループを抜ける
		if (CheckKeyInput(InputHandle) != 0)break;

		//入力モードの描画
		DrawKeyInputModeString(640, 480);

		//入力途中の文字列の描画
		DrawKeyInputString(0, 0, InputHandle);

	}

	//入力された文字列の取得
	GetKeyInputString(String, InputHandle);

	DeleteKeyInput(InputHandle);

	
}

void GameManager::StatusSet(int setType, int value)
{
	//もしATACK上昇させたいなら
	//0:ATACK,...

	//int MAGIATACK;	//魔法攻撃力
	//int MAGIDEFENCE;//魔法防御力
	//int SPEED;		//素早さ
	//int MIND;		//賢さ
	//int VITALITY;	//持久力
	if (0 == setType) {
		for (auto c : chara) {
			if (c->charadata->ATACK <= 0)return;
			c->charadata->ATACK += value;
		}
	}
	//DEFENCE
	else if (1 == setType) {
		for (auto c : chara) {
			if (c->charadata->DEFENCE <= 0)return;
			c->charadata->DEFENCE += value;
		}
	}
	//MAGIATACK
	else if (2 == setType) {
		for (auto c : chara) {
			if (c->charadata->MAGIATACK <= 0)return;
			c->charadata->MAGIATACK += value;
		}
	}
	//MAGIDEFENCE
	else if (3 == setType) {
		for (auto c : chara) {
			if (c->charadata->MAGIDEFENCE <= 0)return;
			c->charadata->MAGIDEFENCE += value;
		}
	}
	//SPEED
	else if (4 == setType) {
		for (auto c : chara) {
			if (c->charadata->SPEED <= 0)return;
			c->charadata->SPEED += value;
		}
	}
	//MIND
	else if (5 == setType) {
		for (auto c : chara) {
			if (c->charadata->MIND <= 0)return;
			c->charadata->MIND += value;
		}
	}
	//VITALITY
	else if (6 == setType) {
		for (auto c : chara) {
			if (c->charadata->VITALITY <= 0)return;
			c->charadata->VITALITY += value;

		}
	}
	//else if

}

/*************Characterに枠ごと実装したためここでは表示しない************
//debug
//TrainingSceneから引数で座標を持ってくる
void GameManager::CharactorStatusDraw()
{
	int i = 0;
	for (auto c : chara) {
		std::string name = c->charadata->name_;
		int ATK = c->charadata->ATACK;
		int DEF = c->charadata->DEFENCE;
		int MATK = c->charadata->MAGIATACK;
		int MDEF = c->charadata->MAGIDEFENCE;
		int SPEED = c->charadata->SPEED;
		int MIND = c->charadata->MIND;
		int VIT = c->charadata->VITALITY;
		DrawStringEx(500 + i * 200, 200, -1, "名前:%s", name.c_str());
		DrawStringEx(500 + i * 200, 240, -1, "攻撃力:%d", ATK);
		DrawStringEx(500 + i * 200, 280, -1, "防御力:%d", DEF);
		DrawStringEx(500 + i * 200, 320, -1, "魔攻撃力:%d", MATK);
		DrawStringEx(500 + i * 200, 360, -1, "魔防御力:%d", MDEF);
		DrawStringEx(500 + i * 200, 400, -1, "速度:%d", SPEED);
		DrawStringEx(500 + i * 200, 440, -1, "賢さ:%d", MIND);
		DrawStringEx(500 + i * 200, 480, -1, "持久力:%d", VIT);

		++i;
	}

}
*/

void GameManager::Update()
{
	SceneManager::Update();
}

void GameManager::Draw()
{
	if (isInput == false) {
		DrawStringEx(800, 500, -1, "false");
	}
	else {
		DrawStringEx(800, 500, -1, "true");
	}
	SceneManager::Render();
	/*if (chara.empty())return;
	CharactorStatusDraw();*/
	
}
