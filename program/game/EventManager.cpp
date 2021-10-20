#include "EventManager.h"
#include<vector>
#include<string>
#include"DxLib.h"
#include"../library//t2klib.h"
#include"GameManager.h"
#include "DxLib.h"
#include<time.h>
#include <iostream>

extern GameManager* gManager;


EventManager::EventManager()
{
	SRand(time(0));

}

void EventManager::loadEvent()
{
	blue_event = t2k::loadCsv("Csv/blueEvent.csv");
	red_event = t2k::loadCsv("Csv/redEvent.csv");
	white_event = t2k::loadCsv("Csv/whiteEvent.csv");

}

int EventManager::setEvent(int eventType)
{


	for (int i = 0; i < 12; ++i) {
		if (i == eventType) {
			return i;

		}
		else {
			continue;
		}
	}


}

void EventManager::DoEvent(int eventID)
{
	if (0 == eventID) {
		//�����łǂ̃X�e�[�^�X���オ�邩�����_���Ō��肷��
		int statusType = Random(6);
		//�X�e�[�^�X���オ��֐����Ăяo��
		//����܂�ǂ��Ȃ��̂ō���ύX�\��
		gManager->StatusSet(statusType, 1);

	}
	else {

		std::cout << "�C�x���g" << "%d\n" << eventID << "�����s���ꂽ��" << std::endl;



	}



}

int EventManager::Random(int rangeMax)
{
	//0����rangeMax�܂ł̐��̗�����Ԃ�
	int hoge = GetRand(rangeMax);


	return hoge;
}
