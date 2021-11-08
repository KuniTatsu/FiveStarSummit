#include "AbilityManager.h"
#include"Ability.h"
#include<vector>
#include<string>
#include"DxLib.h"
#include"../library//t2klib.h"
#include"GameManager.h"
#include "DxLib.h"

extern GameManager* gManager;

AbilityManager::AbilityManager()
{
	//�\�߃C�x���g���X�g��2�����z��̂����̍ŏ��̃J������3��(0,1,2)����Ă���
	//abilityList[0][],abilityList[1][],abilityList[2][] �������
	abilityList.resize(3);
	LoadAbility();
}

AbilityManager::~AbilityManager()
{


}

void AbilityManager::LoadAbility()
{

	ability_all = t2k::loadCsv("Csv/Ability.csv");

	for (int i = 1; i < ability_all.size(); ++i) {

		//id(int)	AbilityType(int)	Ability_Name	ATACK	DEFENCE	MATACK	MDEFENCE	SPEED	MIND	VITALITY	Ability_Desc	Desc rank

		//excel����ǂݎ�����������ϐ��Ɋi�[���A�r���e�B�N���X�𐶐�����Ƃ��̈����ɂԂ�����
		//id
		int a = std::atoi(ability_all[i][0].c_str());
		//AbilityType:0,1,2
		int b = std::atoi(ability_all[i][1].c_str());
		//ATACK
		int c = std::atoi(ability_all[i][3].c_str());
		//DEFENCE
		int d = std::atoi(ability_all[i][4].c_str());
		//MATACK
		int e = std::atoi(ability_all[i][5].c_str());
		//MDEFENCE
		int f = std::atoi(ability_all[i][6].c_str());
		//SPEED
		int g = std::atoi(ability_all[i][7].c_str());
		//MIND
		int h = std::atoi(ability_all[i][8].c_str());
		//VITALITY
		int j = std::atoi(ability_all[i][9].c_str());
		//rank:0,1
		int k = std::atoi(ability_all[i][12].c_str());


		Ability* abi = new Ability(a, b, ability_all[i][2], c, d, e, f, g, h, j, ability_all[i][10], ability_all[i][11], k);

		//abilitytype���ƂɃ��X�g�Ɋi�[
		abilityList[b].emplace_back(abi);


	}
}
