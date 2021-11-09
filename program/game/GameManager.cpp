#include "GameManager.h"
#include"SceneManager.h"
#include"Character.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"
#include<string>
#include"AbilityManager.h"
#include"Ability.h"



GameManager::GameManager()
{
	aManager = new AbilityManager();
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
	////string�^�ɕϊ�
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
	//DrawStringEx(800, 600, -1, "���͒�����");

	//���͂��n�߂����Ƃ����
	SetActiveKeyInput(InputHandle);

	//�ȍ~�̓��͂͂��ׂ�InputHandle�ɍs��

	while (!ProcessMessage()) {


		//�������͂��I�����Ă���Ȃ�while���[�v�𔲂���
		if (CheckKeyInput(InputHandle) != 0)break;

		//���̓��[�h�̕`�恫�o�Ȃ�
		DrawKeyInputModeString(640, 480);
		//���o�Ȃ�
		DrawBox(200, 200, 640, 480, -1, true);

		//���o��
		//t2k::debugTrace("\n���͒�\n");

		//���͓r���̕�����̕`�恫�o�Ȃ�
		DrawKeyInputString(640, 480, InputHandle);

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

			c->charadata->ATACK += value;
			if (c->charadata->ATACK <= 0)c->charadata->ATACK = 0;
		}
	}
	//DEFENCE
	else if (1 == setType) {
		for (auto c : chara) {
			
			c->charadata->DEFENCE += value;
			if (c->charadata->DEFENCE <= 0)c->charadata->DEFENCE = 0;
		}
	}
	//MAGIATACK
	else if (2 == setType) {
		for (auto c : chara) {
			
			c->charadata->MAGIATACK += value;
			if (c->charadata->MAGIATACK <= 0)c->charadata->MAGIATACK = 0;
		}
	}
	//MAGIDEFENCE
	else if (3 == setType) {
		for (auto c : chara) {
			
			c->charadata->MAGIDEFENCE += value;
			if (c->charadata->MAGIDEFENCE <= 0)c->charadata->MAGIDEFENCE = 0;
		}
	}
	//SPEED
	else if (4 == setType) {
		for (auto c : chara) {
			
			c->charadata->SPEED += value;
			if (c->charadata->SPEED <= 0)c->charadata->SPEED = 0;
		}
	}
	//MIND
	else if (5 == setType) {
		for (auto c : chara) {
			
			c->charadata->MIND += value;
			if (c->charadata->MIND <= 0)c->charadata->MIND = 0;
		}
	}
	//VITALITY
	else if (6 == setType) {
		for (auto c : chara) {
			
			c->charadata->VITALITY += value;
			if (c->charadata->VITALITY <= 0)c->charadata->VITALITY = 0;

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

	//debug
	/*std::string hoge = aManager->abilityList[0][0]->ability_name;
	DrawStringEx(800, 700, -1, "%s", hoge);*/

}
