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
	//予めイベントリストの2次元配列のうちの最初のカラムを3つ(0,1,2)作っておく
	//eventList[0][],eventList[1][],eventList[2][] が作られる
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

		//excelから読み取った列を一つずつ変数に格納→イベントクラスを生成するときの引数にぶち込む
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

		//eventtypeごとにリストに格納
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

	//ここ後で変える→受け取ったイベントタイプを元に、excelから読み込んだイベントに振り分けて返す
	if (0 <= eventType && eventType <= 5) {
		return 0;
	}
	else if (6 <= eventType && eventType <= 8) {
		return 1;
	}
	else if (9 <= eventType && eventType <= 15) {
		return 2;
	}

	//for (int i = 0; i < 15; ++i) {
	//	if (i == eventType) {
	//		return i;

	//	}
	//	else {
	//		continue;
	//	}
	//}
}
//イベントを実行する関数 いずれイベントクラスのメンバーを呼び出すようにしたい
void EventManager::DoEvent(int eventID, int randomnum)
{
	//eventID:0,1,2 randomnum:eventnumber
	//どのイベントを行うかexcelから決定する
	eventList[eventID][randomnum]->run_Status_Event();
	//eventList[0][1]->StatusName_;

}

int EventManager::Random(int rangeMax)
{
	//0からrangeMaxまでの数の乱数を返す
	int hoge = GetRand(rangeMax);


	return hoge;
}
