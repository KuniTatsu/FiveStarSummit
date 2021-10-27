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
	chara_ = new Chara();
	chara.emplace_back(chara_);
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
//debug
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

void GameManager::Update()
{
	SceneManager::Update();
}

void GameManager::Draw()
{
	SceneManager::Render();
	if (chara.empty())return;
	CharactorStatusDraw();
}
