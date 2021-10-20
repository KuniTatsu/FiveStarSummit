#include "GameManager.h"
#include"SceneManager.h"
#include"Character.h"



GameManager::GameManager()
{
	//sManager = new SceneManager();
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
	//もしATACK上昇させたいなら
	//0:ATACK,...

	//int MAGIATACK;	//魔法攻撃力
	//int MAGIDEFENCE;//魔法防御力
	//int SPEED;		//素早さ
	//int MIND;		//賢さ
	//int VITALITY;	//持久力
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

void GameManager::Update()
{
	SceneManager::Update();
}

void GameManager::Draw()
{
	SceneManager::Render();
}
