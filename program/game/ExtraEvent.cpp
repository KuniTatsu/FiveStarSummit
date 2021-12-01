#include "ExtraEvent.h"
#include"GameManager.h"
#include"../library/t2klib.h"
#include"../support/Support.h"
#include"DxLib.h"
#include<string>

extern GameManager* gManager;

ExtraEvent::ExtraEvent()
{
	loadCharaRandomName();

}

void ExtraEvent::NewMemberComing()
{
	for (int i = 0; i < 10; ++i) {

		int rand = GetRand(RandomNameList.size()-1);

		std::string randomName = RandomNameList[rand];

		//���O������Ɍ��肵�ăL�����𐶐�����
		gManager->MakeCharacter(randomName);
	}

}

void ExtraEvent::ExitMember()
{



}

void ExtraEvent::loadCharaRandomName()
{
	RandomName_All = t2k::loadCsv("Csv/CharaRandomName.csv");
	for (int i = 1; i < RandomName_All.size(); ++i) {

		//excel����ǂݎ�����������ϐ��Ɋi�[���C�x���g�N���X�𐶐�����Ƃ��̈����ɂԂ�����
		//id
		int a = std::atoi(RandomName_All[i][0].c_str());

		//eventtype���ƂɃ��X�g�Ɋi�[
		RandomNameList.emplace_back(RandomName_All[i][1]);
	}
}



