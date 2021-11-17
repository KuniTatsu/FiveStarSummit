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
	//�\�߃C�x���g���X�g��2�����z��̂����̍ŏ��̃J������3��(0,1,2)����Ă���
	//eventList[0][],eventList[1][],eventList[2][] �������
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

		//excel����ǂݎ�����������ϐ��Ɋi�[���C�x���g�N���X�𐶐�����Ƃ��̈����ɂԂ�����
		//id
		int a = std::atoi(event_all[i][0].c_str());
		//eventType:0,1,2
		int b = std::atoi(event_all[i][1].c_str());
		//extraStatus_type:0,1,2,3,4,5,6
		int c = std::atoi(event_all[i][2].c_str());
		//extraStatus_num:increase number;
		int d = std::atoi(event_all[i][3].c_str());

		//id,eventType,extraStatus_type,extraStatus_num,desc
		Event* event = new Event(a, b, c, d, event_all[i][4], event_all[i][5]);

		//eventtype���ƂɃ��X�g�Ɋi�[
		eventList[b].emplace_back(event);

		/*int size = eventList[0].size();
		int rand = GetRand(size-1);
		eventList[0][rand]->run_Event();*/
	}
}

int EventManager::setEvent(int eventType)
{
	//0->5 =>0
	//6->8 =>1
	//9->15 =>2

	//������ŕς��遨�󂯎�����C�x���g�^�C�v�����ɁAexcel����ǂݍ��񂾃C�x���g�ɐU�蕪���ĕԂ�
	if (0 <= eventType && eventType <= 5) {
		return 0;
	}
	else if (6 <= eventType && eventType <= 8) {
		return 1;
	}
	else if (9 <= eventType && eventType <= 15) {
		return 2;
	}

	
}
void EventManager::loadCardEvent()
{
	cardEvent_all=t2k::loadCsv("Csv/cardEvent.csv");



}
//�C�x���g�����s����֐� ������C�x���g�N���X�̃����o�[���Ăяo���悤�ɂ�����
void EventManager::DoEvent(int eventID, int randomnum)
{
	//eventID:0,1,2 randomnum:eventnumber
	//�ǂ̃C�x���g���s����excel���猈�肷��
	eventList[eventID][randomnum]->run_Status_Event();
	//eventList[0][1]->StatusName_;

}

int EventManager::Random(int rangeMax)
{
	//0����rangeMax�܂ł̐��̗�����Ԃ�
	int hoge = GetRand(rangeMax);


	return hoge;
}
