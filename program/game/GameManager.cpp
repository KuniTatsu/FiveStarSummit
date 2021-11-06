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
	
	//string�^�ɕϊ�
	std::string name(String, sizeof(String) / sizeof(String[0]));
	isInput = false;

	chara_ = new Chara(name);
	chara.emplace_back(chara_);
}

void GameManager::InputName()
{
	isInput = true;

	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);


	//���͂��n�߂����Ƃ����
	SetActiveKeyInput(InputHandle);

	//�ȍ~�̓��͂͂��ׂ�InputHandle�ɍs��

	while (!ProcessMessage()) {

		//�������͂��I�����Ă���Ȃ�while���[�v�𔲂���
		if (CheckKeyInput(InputHandle) != 0)break;

		//���̓��[�h�̕`��
		DrawKeyInputModeString(640, 480);

		//���͓r���̕�����̕`��
		DrawKeyInputString(0, 0, InputHandle);

	}

	//���͂��ꂽ������̎擾
	GetKeyInputString(String, InputHandle);

	DeleteKeyInput(InputHandle);

	
}

void GameManager::StatusSet(int setType, int value)
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

/*************Character�ɘg���Ǝ����������߂����ł͕\�����Ȃ�************
//debug
//TrainingScene��������ō��W�������Ă���
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
