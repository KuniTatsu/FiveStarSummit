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
	Character* character = new Character();
	chara.emplace_back(character);
}

void GameManager::StatusSet(int setType)
{
	//����ATACK�㏸���������Ȃ�
	//0:ATACK,...
	if (0 == setType) {
		for (auto c : chara) {
			c.charadata->ATACK += 10;
		}
	}
	else if (1 == setType) {

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
