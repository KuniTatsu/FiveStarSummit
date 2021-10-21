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
	//����ATACK�㏸���������Ȃ�
	//0:ATACK,...

	//int MAGIATACK;	//���@�U����
	//int MAGIDEFENCE;//���@�h���
	//int SPEED;		//�f����
	//int MIND;		//����
	//int VITALITY;	//���v��
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
		DrawStringEx(500 + i * 200, 200, -1, "���O:%s", name.c_str());
		DrawStringEx(500 + i * 200, 240, -1, "�U����:%d", ATK);
		DrawStringEx(500 + i * 200, 280, -1, "�h���:%d", DEF);
		DrawStringEx(500 + i * 200, 320, -1, "���U����:%d", MATK);
		DrawStringEx(500 + i * 200, 360, -1, "���h���:%d", MDEF);
		DrawStringEx(500 + i * 200, 400, -1, "���x:%d", SPEED);
		DrawStringEx(500 + i * 200, 440, -1, "����:%d", MIND);
		DrawStringEx(500 + i * 200, 480, -1, "���v��:%d", VIT);

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
