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

void GameManager::StatusSet(int setType, int valueEx)
{
	//‚à‚µATACKã¸‚³‚¹‚½‚¢‚È‚ç
	//0:ATACK,...

	//int MAGIATACK;	//–‚–@UŒ‚—Í
	//int MAGIDEFENCE;//–‚–@–hŒä—Í
	//int SPEED;		//‘f‘‚³
	//int MIND;		//Œ«‚³
	//int VITALITY;	//‹v—Í
	if (0 == setType) {
		for (auto c : chara) {
			c->charadata->ATACK += 10 * valueEx;
		}
	}
	//DEFENCE
	else if (1 == setType) {
		for (auto c : chara) {
			c->charadata->DEFENCE += 10 * valueEx;
		}
	}
	//MAGIATACK
	else if (2 == setType) {
		for (auto c : chara) {
			c->charadata->MAGIATACK += 10 * valueEx;
		}
	}
	//MAGIDEFENCE
	else if (3 == setType) {
		for (auto c : chara) {
			c->charadata->MAGIDEFENCE += 10 * valueEx;
		}
	}
	//SPEED
	else if (4 == setType) {
		for (auto c : chara) {
			c->charadata->SPEED += 10 * valueEx;
		}
	}
	//MIND
	else if (5 == setType) {
		for (auto c : chara) {
			c->charadata->MIND += 10 * valueEx;
		}
	}
	//VITALITY
	else if (6 == setType) {
		for (auto c : chara) {
			c->charadata->VITALITY += 10 * valueEx;

		}
	}
	//else if

}

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
		DrawStringEx(500 + i * 200, 200, -1, "–¼‘O:%s", name.c_str());
		DrawStringEx(500 + i * 200, 240, -1, "UŒ‚—Í:%d", ATK);
		DrawStringEx(500 + i * 200, 280, -1, "–hŒä—Í:%d", DEF);
		DrawStringEx(500 + i * 200, 320, -1, "–‚UŒ‚—Í:%d", MATK);
		DrawStringEx(500 + i * 200, 360, -1, "–‚–hŒä—Í:%d", MDEF);
		DrawStringEx(500 + i * 200, 400, -1, "‘¬“x:%d", SPEED);
		DrawStringEx(500 + i * 200, 440, -1, "Œ«‚³:%d", MIND);
		DrawStringEx(500 + i * 200, 480, -1, "‹v—Í:%d", VIT);

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
