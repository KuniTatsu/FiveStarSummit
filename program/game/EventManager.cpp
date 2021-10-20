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
		//ここでどのステータスが上がるかランダムで決定する
		int statusType = Random(6);
		//ステータスが上がる関数を呼び出す
		//あんまり良くないので今後変更予定
		gManager->StatusSet(statusType, 1);

	}
	else {

		std::cout << "イベント" << "%d\n" << eventID << "が実行されたよ" << std::endl;



	}



}

int EventManager::Random(int rangeMax)
{
	//0からrangeMaxまでの数の乱数を返す
	int hoge = GetRand(rangeMax);


	return hoge;
}
