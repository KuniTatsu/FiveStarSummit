#include "EventManager.h"
#include<vector>
#include<string>
#include"DxLib.h"
#include"../library//t2klib.h"
#include"GameManager.h"
#include "DxLib.h"
#include<time.h>
#include <iostream>
#include"Event.h"

extern GameManager* gManager;


EventManager::EventManager()
{
	SRand(time(0));
	eventList.resize(3);

	loadEvent();


}

void EventManager::loadEvent()
{
	//�C�x���gCSV�͈�ł悭�ˁH
	/*blue_event = t2k::loadCsv("Csv/blueEvent.csv");
	red_event = t2k::loadCsv("Csv/redEvent.csv");
	white_event = t2k::loadCsv("Csv/whiteEvent.csv");*/

	event_all = t2k::loadCsv("Csv/event.csv");
	for (int i = 1; i < event_all.size(); ++i) {

		//id
		int a = std::atoi(event_all[i][0].c_str());
		//eventType:0,1,2
		int b = std::atoi(event_all[i][1].c_str());
		//extraStatus_type:0,1,2,3,4,5,6
		int c = std::atoi(event_all[i][2].c_str());
		//extraStatus_num:increase number;
		int d = std::atoi(event_all[i][3].c_str());

		Event* event = new Event(a, b, c, d, event_all[i][4]);

		eventList[b].emplace_back(event);

		/*int size = eventList[0].size();
		int rand = GetRand(size-1);
		eventList[0][rand]->run_Event();*/
	}
}

int EventManager::setEvent(int eventType)
{

	//������ŕς��遨�󂯎�����C�x���g�^�C�v�����ɁAexcel����ǂݍ��񂾃C�x���g�ɐU�蕪���ĕԂ�

	for (int i = 0; i < 12; ++i) {
		if (i == eventType) {
			return i;

		}
		else {
			continue;
		}
	}
}
//�C�x���g�����s����֐� ������C�x���g�N���X�̃����o�[���Ăяo���悤�ɂ�����
void EventManager::DoEvent(int eventID,int randomnum)
{
	//�������ڐA����
	//int size = eventList[eventID].size();
	//int rand = GetRand(size - 1);


	eventList[eventID][randomnum]->run_Event();


	//if (0 == eventID) {
	//	//�����łǂ̃X�e�[�^�X���オ�邩�����_���Ō��肷��
	//	int statusType = Random(6);
	//	//�X�e�[�^�X���オ��֐����Ăяo��
	//	//����܂�ǂ��Ȃ��̂ō���ύX�\��
	//	gManager->StatusSet(statusType, 1);
	//	//------debug------
	//	eventdebugID = eventID;
	//	//-------------------
	//}
	//else {
	//	//------debug------
	//	eventdebugID = eventID;

	//	//std::cout << "�C�x���g" << "%d\n" << eventID << "�����s���ꂽ��" << std::endl;

	//}



}

int EventManager::Random(int rangeMax)
{
	//0����rangeMax�܂ł̐��̗�����Ԃ�
	int hoge = GetRand(rangeMax);


	return hoge;
}
