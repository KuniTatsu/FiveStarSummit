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

	//InputName();
	//
	////stringå^Ç…ïœä∑
	//std::string name(String, sizeof(String) / sizeof(String[0]));
	//isInput = false;
	 
	//******debug*****
	std::string name = "test";

	chara_ = new Chara(name);
	chara.emplace_back(chara_);
}

void GameManager::InputName()
{
	isInput = true;

	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	//DrawStringEx(800, 600, -1, "ì¸óÕíÜÇæÇÊ");

	//ì¸óÕÇénÇﬂÇΩÇ¢Ç∆Ç±ÇÎÇ≈
	SetActiveKeyInput(InputHandle);

	//à»ç~ÇÃì¸óÕÇÕÇ∑Ç◊ÇƒInputHandleÇ…çsÇ≠

	while (!ProcessMessage()) {


		//ï∂éöì¸óÕÇ™èIóπÇµÇƒÇ¢ÇÈÇ»ÇÁwhileÉãÅ[ÉvÇî≤ÇØÇÈ
		if (CheckKeyInput(InputHandle) != 0)break;

		//ì¸óÕÉÇÅ[ÉhÇÃï`âÊÅ´èoÇ»Ç¢
		DrawKeyInputModeString(640, 480);
		//Å´èoÇ»Ç¢
		DrawBox(200, 200, 640, 480, -1, true);

		//Å´èoÇÈ
		//t2k::debugTrace("\nì¸óÕíÜ\n");

		//ì¸óÕìríÜÇÃï∂éöóÒÇÃï`âÊÅ´èoÇ»Ç¢
		DrawKeyInputString(640, 480, InputHandle);

	}

	//ì¸óÕÇ≥ÇÍÇΩï∂éöóÒÇÃéÊìæ
	GetKeyInputString(String, InputHandle);

	DeleteKeyInput(InputHandle);

	
}

void GameManager::StatusSet(int setType, int value)
{
	//Ç‡ÇµATACKè„è∏Ç≥ÇπÇΩÇ¢Ç»ÇÁ
	//0:ATACK,...

	//int MAGIATACK;	//ñÇñ@çUåÇóÕ
	//int MAGIDEFENCE;//ñÇñ@ñhå‰óÕ
	//int SPEED;		//ëfëÅÇ≥
	//int MIND;		//å´Ç≥
	//int VITALITY;	//éùãvóÕ
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

/*************CharacterÇ…ògÇ≤Ç∆é¿ëïÇµÇΩÇΩÇﬂÇ±Ç±Ç≈ÇÕï\é¶ÇµÇ»Ç¢************
//debug
//TrainingSceneÇ©ÇÁà¯êîÇ≈ç¿ïWÇéùÇ¡ÇƒÇ≠ÇÈ
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
		DrawStringEx(500 + i * 200, 200, -1, "ñºëO:%s", name.c_str());
		DrawStringEx(500 + i * 200, 240, -1, "çUåÇóÕ:%d", ATK);
		DrawStringEx(500 + i * 200, 280, -1, "ñhå‰óÕ:%d", DEF);
		DrawStringEx(500 + i * 200, 320, -1, "ñÇçUåÇóÕ:%d", MATK);
		DrawStringEx(500 + i * 200, 360, -1, "ñÇñhå‰óÕ:%d", MDEF);
		DrawStringEx(500 + i * 200, 400, -1, "ë¨ìx:%d", SPEED);
		DrawStringEx(500 + i * 200, 440, -1, "å´Ç≥:%d", MIND);
		DrawStringEx(500 + i * 200, 480, -1, "éùãvóÕ:%d", VIT);

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
