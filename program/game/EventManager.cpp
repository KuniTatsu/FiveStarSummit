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
	//イベントCSVは一つでよくね？
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

	//ここ後で変える→受け取ったイベントタイプを元に、excelから読み込んだイベントに振り分けて返す

	for (int i = 0; i < 12; ++i) {
		if (i == eventType) {
			return i;

		}
		else {
			continue;
		}
	}
}
//イベントを実行する関数 いずれイベントクラスのメンバーを呼び出すようにしたい
void EventManager::DoEvent(int eventID,int randomnum)
{
	//ここを移植する
	//int size = eventList[eventID].size();
	//int rand = GetRand(size - 1);


	eventList[eventID][randomnum]->run_Event();


	//if (0 == eventID) {
	//	//ここでどのステータスが上がるかランダムで決定する
	//	int statusType = Random(6);
	//	//ステータスが上がる関数を呼び出す
	//	//あんまり良くないので今後変更予定
	//	gManager->StatusSet(statusType, 1);
	//	//------debug------
	//	eventdebugID = eventID;
	//	//-------------------
	//}
	//else {
	//	//------debug------
	//	eventdebugID = eventID;

	//	//std::cout << "イベント" << "%d\n" << eventID << "が実行されたよ" << std::endl;

	//}



}

int EventManager::Random(int rangeMax)
{
	//0からrangeMaxまでの数の乱数を返す
	int hoge = GetRand(rangeMax);


	return hoge;
}
