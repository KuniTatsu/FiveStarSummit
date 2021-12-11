#include "ExtraEvent.h"
#include"GameManager.h"
#include"../library/t2klib.h"
#include"../support/Support.h"
#include"DxLib.h"
#include<string>
#include"Character.h"

extern GameManager* gManager;

ExtraEvent::ExtraEvent()
{
	loadCharaRandomName();

}

//�������O�̃L�������쐬����Ȃ��悤�ɂ�����
void ExtraEvent::NewMemberComing(int year)
{
	//for (int i = 0; i < 10; ++i) {
	int count = 0;
	//10�l���܂ő�����
	while (count < 10) {
		std::string choosenName = ChooseName();

		bool checkAlreadyUseName = false;

		//���łɎg���Ă���L����������Ȃ����m�F����
		for (auto name : usedNameList) {
			if (name == choosenName) {
				//���łɎg���Ă�����t���O��true�ɂ���
				checkAlreadyUseName = true;
				break;
			}
			else {
				continue;
			}

		}
		if (checkAlreadyUseName == false) {
			//�g�������O���X�g�ɓo�^����
			usedNameList.emplace_back(choosenName);
			count++;
			//���O������Ɍ��肵�ăL�����𐶐�����
			gManager->MakeCharacter(choosenName,year);
		}
	}
	//}
	//���Ǝ��Ŏg�������O���X�g���N���A����
	//usedNameList.clear();
}

void ExtraEvent::ExitMember()
{
	gManager->ExitCharaVec();
	
	
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

std::string ExtraEvent::ChooseName()
{
	int rand = GetRand(RandomNameList.size() - 1);

	std::string randomName = RandomNameList[rand];
	//usedNameList.emplace_back(randomName);

	return randomName;
}



