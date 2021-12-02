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

//同じ名前のキャラが作成されないようにしたい
void ExtraEvent::NewMemberComing()
{
	//for (int i = 0; i < 10; ++i) {
	int count = 0;
	//10人作るまで続ける
	while (count < 10) {
		std::string choosenName = ChooseName();

		bool checkAlreadyUseName = false;

		//すでに使っているキャラ名じゃないか確認する
		for (auto name : usedNameList) {
			if (name == choosenName) {
				//すでに使われていたらフラグをtrueにする
				checkAlreadyUseName = true;
				break;
			}
			else {
				continue;
			}

		}
		if (checkAlreadyUseName == false) {
			//使った名前リストに登録する
			usedNameList.emplace_back(choosenName);
			count++;
			//名前を勝手に決定してキャラを生成する
			gManager->MakeCharacter(choosenName);
		}
	}
	//}
	//卒業式で使った名前リストをクリアする
	//usedNameList.clear();
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

std::string ExtraEvent::ChooseName()
{
	int rand = GetRand(RandomNameList.size() - 1);

	std::string randomName = RandomNameList[rand];
	//usedNameList.emplace_back(randomName);

	return randomName;
}



