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

}

GameManager::~GameManager()
{
}

void GameManager::MakeCharacter(const std::string& name, int year)
{
	chara_ = new Chara(name, year);

	int random = GetRand(charaGh.size() - 1);
	//chara_->gh


	chara_->gh = SetCharaGh(random);

	chara.emplace_back(chara_);
	//InputName(name);
}

void GameManager::ExitCharaVec()
{
	auto it = chara.begin();
	while (it != chara.end()) {
		if ((*it)->charadata->stayYear == 3) {
			exitChara.emplace_back((*it));
			it = chara.erase(it);
			continue;
		}
		it++;
	}


}

void GameManager::InputName(std::string name)
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

	if (0 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_ATACK += value;
			if (c->charadata->EXP_ATACK <= 0)c->charadata->EXP_ATACK = 0;
			if (c->charadata->EXP_ATACK >= needExp[GetDecNum(c->charadata->ATACK)]) {
				c->charadata->ATACK += 1;
				c->charadata->EXP_ATACK = 0;
			}
		}
	}
	//DEFENCE
	else if (1 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_DEFENCE += value;
			if (c->charadata->EXP_DEFENCE <= 0)c->charadata->EXP_DEFENCE = 0;
			if (c->charadata->EXP_DEFENCE >= needExp[GetDecNum(c->charadata->DEFENCE)]) {
				c->charadata->DEFENCE += 1;
				c->charadata->EXP_DEFENCE = 0;
			}
		}
	}
	//MAGIATACK
	else if (2 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_MAGIATACK += value;
			if (c->charadata->EXP_MAGIATACK <= 0)c->charadata->EXP_MAGIATACK = 0;
			if (c->charadata->EXP_MAGIATACK >= needExp[GetDecNum(c->charadata->MAGIATACK)]) {
				c->charadata->MAGIATACK += 1;
				c->charadata->EXP_MAGIATACK = 0;
			}
		}
	}
	//MAGIDEFENCE
	else if (3 == setType) {
		for (auto c : chara) {

			c->charadata->MAGIDEFENCE += value;
			if (c->charadata->EXP_MAGIDEFENCE <= 0)c->charadata->EXP_MAGIDEFENCE = 0;
			if (c->charadata->EXP_MAGIDEFENCE >= needExp[GetDecNum(c->charadata->MAGIDEFENCE)]) {
				c->charadata->MAGIDEFENCE += 1;
				c->charadata->EXP_MAGIDEFENCE = 0;
			}
		}
	}
	//SPEED
	else if (4 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_SPEED += value;
			if (c->charadata->EXP_SPEED <= 0)c->charadata->EXP_SPEED = 0;
			if (c->charadata->EXP_SPEED >= needExp[GetDecNum(c->charadata->SPEED)]) {
				c->charadata->SPEED += 1;
				c->charadata->EXP_SPEED = 0;
			}
		}
	}
	//MIND
	else if (5 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_MIND += value;
			if (c->charadata->EXP_MIND <= 0)c->charadata->EXP_MIND = 0;
			if (c->charadata->EXP_MIND >= needExp[GetDecNum(c->charadata->MIND)]) {
				c->charadata->MIND += 1;
				c->charadata->EXP_MIND = 0;
			}
		}
	}
	//VITALITY
	else if (6 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_VITALITY += value;
			if (c->charadata->EXP_VITALITY <= 0)c->charadata->EXP_VITALITY = 0;
			if (c->charadata->EXP_VITALITY >= needExp[GetDecNum(c->charadata->VITALITY)]) {
				c->charadata->VITALITY += 1;
				c->charadata->EXP_VITALITY = 0;
			}

		}
	}
	//else if

}

void GameManager::StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit)
{

	for (auto c : chara) {

		c->charadata->EXP_ATACK += atk;
		c->charadata->EXP_DEFENCE += def;
		c->charadata->EXP_MAGIATACK += magiatk;
		c->charadata->EXP_MAGIDEFENCE += magidef;
		c->charadata->EXP_SPEED += spd;
		c->charadata->EXP_MIND += mind;
		c->charadata->EXP_VITALITY += vit;


		if (c->charadata->EXP_ATACK >= needExp[GetDecNum(c->charadata->ATACK)]) {
			c->charadata->ATACK += 1;
			c->charadata->EXP_ATACK = 0;
		}

		if (c->charadata->EXP_DEFENCE >= needExp[GetDecNum(c->charadata->DEFENCE)]) {
			c->charadata->DEFENCE += 1;
			c->charadata->EXP_DEFENCE = 0;
		}

		if (c->charadata->EXP_MAGIATACK >= needExp[GetDecNum(c->charadata->MAGIATACK)]) {
			c->charadata->MAGIATACK += 1;
			c->charadata->EXP_MAGIATACK = 0;
		}

		if (c->charadata->EXP_MAGIDEFENCE >= needExp[GetDecNum(c->charadata->MAGIDEFENCE)]) {
			c->charadata->MAGIDEFENCE += 1;
			c->charadata->EXP_MAGIDEFENCE = 0;
		}

		if (c->charadata->EXP_SPEED >= needExp[GetDecNum(c->charadata->SPEED)]) {
			c->charadata->SPEED += 1;
			c->charadata->EXP_SPEED = 0;
		}

		if (c->charadata->EXP_MIND >= needExp[GetDecNum(c->charadata->MIND)]) {
			c->charadata->MIND += 1;
			c->charadata->EXP_MIND = 0;
		}

		if (c->charadata->EXP_VITALITY >= needExp[GetDecNum(c->charadata->VITALITY)]) {
			c->charadata->VITALITY += 1;
			c->charadata->EXP_VITALITY = 0;
		}



		/*if (c->charadata->ATACK <= 0)c->charadata->ATACK = 0;
		if (c->charadata->DEFENCE <= 0)c->charadata->DEFENCE = 0;
		if (c->charadata->MAGIATACK <= 0)c->charadata->MAGIATACK = 0;
		if (c->charadata->MAGIDEFENCE <= 0)c->charadata->MAGIDEFENCE = 0;
		if (c->charadata->SPEED <= 0)c->charadata->SPEED = 0;
		if (c->charadata->MIND <= 0)c->charadata->MIND = 0;
		if (c->charadata->VITALITY <= 0)c->charadata->VITALITY = 0;*/
	}

}

void GameManager::AbilitySet(int abilityType, int abilityId)
{
	//�Ō�̃L�����̎��_��count��0�Ȃ炻�̃L�����ɃA�r���e�B��t�^����H�H
	int count = 0;
	for (auto c : chara) {
		//1/10�̊m���ŃA�r���e�B��t�^����
		//int random = GetRand(10);
		int random = 9;
		if (random > 8) {

			//*******�Ȃ񂩕��������A�r���e�B���o�^����Ă�o�O����*******//
			bool checkAlreadyhave = false;
			int i = 0;
			//������for�������܂�����ĂȂ�
			//���łɎ����Ă���A�r���e�B��������ǉ������ɔ�΂�
			for (auto abi : c->charadata->Ability) {

				if (abi->ability_name == aManager->abilityList[abilityType][abilityId]->ability_name) {
					checkAlreadyhave = true;
					break;
				}
				//i++;
			}
			if (checkAlreadyhave) {
				checkAlreadyhave = false;
				continue;
			}
			c->charadata->Ability.emplace_back(aManager->abilityList[abilityType][abilityId]);
			c->recentAddedAbility = aManager->abilityList[abilityType][abilityId]->ability_name;
			count += 1;

		}

	}
}
void GameManager::TrainingSet(Chara* setChara,int id)
{
	setChara->charadata->training_ToDo = id;
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


		chara_ = new Chara(name, 1);
		chara.emplace_back(chara_);


	}
	else {
		//���̓��[�h�̕`��
		DrawKeyInputModeString(640, 480);

		//���o��
		//t2k::debugTrace("\n���͒�\n");

		//DrawBox(50, 50, 100, 100, -1, true);
		//���͓r���̕�����̕`��
		DrawKeyInputString(200, 200, InputHandle);
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
	loadCharaCsv();
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

std::vector<int> GameManager::SetCharaGh(int num)
{
	return charaGh[num];
}



std::string GameManager::GetAbility(int abilityType, int abilityId)
{
	std::string ability = aManager->abilityList[abilityType][abilityId]->ability_name;

	return ability;
}

void GameManager::loadCharaCsv()
{
	loadGhCsv = t2k::loadCsv("Csv/CharaPass.csv");
	for (int i = 1; i < loadGhCsv.size() - 1; ++i) {

		int hoge[3] = {};
		std::string Pass = loadGhCsv[i][1];
		LoadDivGraph(Pass.c_str(), 3, 3, 1, 32, 32, hoge, false);


		std::vector<int> gh;
		charaGh.emplace_back(gh);
		charaGh[i - 1].emplace_back(hoge[0]);
		charaGh[i - 1].emplace_back(hoge[1]);
		charaGh[i - 1].emplace_back(hoge[2]);
	}
}

int GameManager::GetDecNum(int nowStatus)
{
	if (nowStatus >= 90 && nowStatus < 96) {

		return 10;
	}
	else if (nowStatus >= 96) {
		return 9;
	}
	int DecNum = nowStatus / 10;

	return DecNum;
}

