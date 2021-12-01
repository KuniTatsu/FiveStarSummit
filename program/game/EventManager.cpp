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
#include "CardEvent.h"
#include"ForceStopDay.h"
#include"ExtraEvent.h"


extern GameManager* gManager;


EventManager::EventManager()
{
	SRand(time(0));
	//予めイベントリストの2次元配列のうちの最初のカラムを3つ(0,1,2)作っておく
	//eventList[0][],eventList[1][],eventList[2][] が作られる
	eventList.resize(3);

	cardEventList.resize(3);

	loadEvent();
	loadCardEvent();
	loadForcedStopDay();
	exEvent = new ExtraEvent();
}

void EventManager::loadEvent()
{
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
	else if (eventType >= 16) {
		return 99;
	}

	
}
void EventManager::loadCardEvent()
{
	cardEvent_all=t2k::loadCsv("Csv/cardEvent.csv");
	for (int i = 1; i < cardEvent_all.size(); ++i) {

		//excelから読み取った列を一つずつ変数に格納→イベントクラスを生成するときの引数にぶち込む
		//id
		int a = std::atoi(cardEvent_all[i][0].c_str());
		//eventType:0,1,2
		int b = std::atoi(cardEvent_all[i][1].c_str());
		//atk
		int c = std::atoi(cardEvent_all[i][2].c_str());
		//def
		int d = std::atoi(cardEvent_all[i][3].c_str());
		//matk
		int e = std::atoi(cardEvent_all[i][4].c_str());
		//mdef
		int f = std::atoi(cardEvent_all[i][5].c_str());
		//spd
		int g = std::atoi(cardEvent_all[i][6].c_str());
		//mind
		int h = std::atoi(cardEvent_all[i][7].c_str());
		//vit
		int j = std::atoi(cardEvent_all[i][8].c_str());
		//AbilityType
		int k = std::atoi(cardEvent_all[i][10].c_str());
		//AbilityId
		int l = std::atoi(cardEvent_all[i][11].c_str());
		//tension
		int m = std::atoi(cardEvent_all[i][12].c_str());
		//ItemId
		int n = std::atoi(cardEvent_all[i][13].c_str());

		//id(int)	eventType(int)	atk	def	matk	mdef	spd	mind	vit	desc(std::string)	Abilitytype(int)	Abilityid(int)	tension(int)	itemid(int)
		CardEvent* event = new CardEvent(a, b, c, d, e,f,g,h,j,cardEvent_all[i][9], k,l,m,n);

		//eventtypeごとにリストに格納
		cardEventList[b].emplace_back(event);

		/*int size = eventList[0].size();
		int rand = GetRand(size-1);
		eventList[0][rand]->run_Event();*/
	}


}
//イベントを実行する関数 いずれイベントクラスのメンバーを呼び出すようにしたい
void EventManager::DoEvent(int eventID, int randomnum)
{
	//eventID:0,1,2 randomnum:eventnumber
	//どのイベントを行うかexcelから決定する
	if (eventID == 99)return;
	eventList[eventID][randomnum]->run_Status_Event();
	//eventList[0][1]->StatusName_;

}

void EventManager::DoCardEvent(int eventType, int eventId)
{

	cardEventList[eventType][eventId]->run_Card_Event();

}

int EventManager::Random(int rangeMax)
{
	//0からrangeMaxまでの数の乱数を返す
	int hoge = GetRand(rangeMax);


	return hoge;
}

void EventManager::loadForcedStopDay()
{
	ForcedStopDay_All = t2k::loadCsv("Csv/ForcedStopDay.csv");
	for (int i = 1; i < ForcedStopDay_All.size(); ++i) {
		//id
		int a = std::atoi(ForcedStopDay_All[i][0].c_str());
		//month
		int b = std::atoi(ForcedStopDay_All[i][1].c_str());
		//day
		int c = std::atoi(ForcedStopDay_All[i][2].c_str());

		ForcedStopDay* stopday = new ForcedStopDay(a, b, c, ForcedStopDay_All[i][3]);

		ForcedStopDayList.emplace_back(stopday);

	}
}
