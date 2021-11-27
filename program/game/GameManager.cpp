#include "GameManager.h"
#include"SceneManager.h"
#include"Character.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"
#include<string>
#include"AbilityManager.h"
#include"Ability.h"
#include"DataManager.h"



GameManager::GameManager()
{
	//aManager = new AbilityManager();
	////dManager = new DataManager();
	////sManager = new SceneManager();
	//deitatime_ = 0;

	//SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);
}

GameManager::~GameManager()
{
}

void GameManager::MakeCharacter()
{

	InputName();

	////string�^�ɕϊ�
	//std::string name(String, sizeof(String) / sizeof(String[0]));
	//isInput = false;

	//////******debug*****
	////std::string name = "test";


	//chara_ = new Chara(name);
	//chara.emplace_back(chara_);


}

void GameManager::InputName()
{
	isInput = true;
	if (InputHandle != 0)return;
	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	//DrawStringEx(800, 600, -1, "���͒�����");

	//���͂��n�߂����Ƃ����
	SetActiveKeyInput(InputHandle);

	//�ȍ~�̓��͂͂��ׂ�InputHandle�ɍs��

	//���t���[�����s���K�v�Ȃ̂�Update�Ɉړ�
#if 0

	while (!ProcessMessage()) {


		//�������͂��I�����Ă���Ȃ�while���[�v�𔲂���
		//if (CheckKeyInput(InputHandle) != 0)break;

		//���̓��[�h�̕`�恫�o�Ȃ�
		DrawKeyInputModeString(640, 480);
		//���o�Ȃ�
		DrawBox(200, 200, 640, 480, -1, true);

		//���o��
		//t2k::debugTrace("\n���͒�\n");

		//���͓r���̕�����̕`�恫�o�Ȃ�
		DrawKeyInputString(0, 0, InputHandle);

	}

	//���͂��ꂽ������̎擾
	GetKeyInputString(String, InputHandle);

	DeleteKeyInput(InputHandle);
#endif


}

//�X�L���t�^�C�x���g�͕��̒l�������ꍇ��������R�[�h��`���ɓ����

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

void GameManager::StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit)
{

	for (auto c : chara) {

		c->charadata->ATACK += atk;
		c->charadata->DEFENCE += def;
		c->charadata->MAGIATACK += magiatk;
		c->charadata->MAGIDEFENCE += magidef;
		c->charadata->SPEED += spd;
		c->charadata->MIND += mind;
		c->charadata->VITALITY += vit;

		if (c->charadata->ATACK <= 0)c->charadata->ATACK = 0;
		if (c->charadata->DEFENCE <= 0)c->charadata->DEFENCE = 0;
		if (c->charadata->MAGIATACK <= 0)c->charadata->MAGIATACK = 0;
		if (c->charadata->MAGIDEFENCE <= 0)c->charadata->MAGIDEFENCE = 0;
		if (c->charadata->SPEED <= 0)c->charadata->SPEED = 0;
		if (c->charadata->MIND <= 0)c->charadata->MIND = 0;
		if (c->charadata->VITALITY <= 0)c->charadata->VITALITY = 0;
	}

}

void GameManager::AbilitySet(int abilityType, int abilityId)
{
	int count = 0;
	for (auto c : chara) {
		//1/10�̊m���ŃA�r���e�B��t�^����
		int random = GetRand(10);
		if (random > 8) {

			c->charadata->Ability.emplace_back(aManager->abilityList[abilityType][abilityId]);
			count += 1;
		}
		
	}
}



void GameManager::Update()
{
	SceneManager::Update();

	//�������͂��I�����Ă���Ȃ�while���[�v�𔲂���
	if (InputHandle != 0 && CheckKeyInput(InputHandle) != 0) {

		//���͂��ꂽ������̎擾
		GetKeyInputString(String, InputHandle);

		DeleteKeyInput(InputHandle);
		InputHandle = 0;
		//string�^�ɕϊ�
		std::string name(String, sizeof(String) / sizeof(String[0]));
		isInput = false;

		////******debug*****
		//std::string name = "test";


		chara_ = new Chara(name);
		chara.emplace_back(chara_);


	}
	else {


		//���̓��[�h�̕`�恫�o�Ȃ�
		DrawKeyInputModeString(640, 480);

		//���o��
		//t2k::debugTrace("\n���͒�\n");

		//���͓r���̕�����̕`�恫�o�Ȃ�
		DrawKeyInputString(0, 0, InputHandle);
	}

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

void GameManager::initGameManager()
{
	aManager = new AbilityManager();
	//dManager = new DataManager();
	//sManager = new SceneManager();
	deitatime_ = 0;

	SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);


}

int GameManager::LoadGraphEx(std::string gh)
{

	auto it = ghmap.find(gh);
	if (it != ghmap.end()) {
		return ghmap[gh];
	}

	else {
		int loadgh = LoadGraph(gh.c_str());
		ghmap.insert(std::make_pair(gh, loadgh));
	}


	return ghmap[gh];
}

std::string GameManager::GetAbility(int abilityType, int abilityId)
{
	std::string ability = aManager->abilityList[abilityType][abilityId]->ability_name;

	return ability;
}
