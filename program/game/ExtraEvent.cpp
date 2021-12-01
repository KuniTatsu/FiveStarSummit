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

		//名前を勝手に決定してキャラを生成する
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

		//excelから読み取った列を一つずつ変数に格納→イベントクラスを生成するときの引数にぶち込む
		//id
		int a = std::atoi(RandomName_All[i][0].c_str());

		//eventtypeごとにリストに格納
		RandomNameList.emplace_back(RandomName_All[i][1]);
	}
}



