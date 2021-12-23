#include "DayCell.h"
#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "SceneManager.h"
#include "TrainingScene.h"
#include<time.h>
#include"GameManager.h"


extern GameManager* gManager;

DayCell::DayCell(int cell_gh)
{
	//SRand(time(0));

	if (0 <= cell_gh && cell_gh <= 5) {
		//0は青マス プラス効果のイベントが発生する
		gh = gManager->LoadGraphEx("graphics/blue.png");

	}
	else if (6 <= cell_gh && cell_gh <= 8) {
		//1は赤マス マイナス効果のイベントが発生する
		gh = gManager->LoadGraphEx("graphics/red.png");
	}
	else if (9 <= cell_gh && cell_gh <= 14) {
		//2は白マス プラス効果とマイナス効果がランダムで選ばれる
		//出来れば4~10月はプラスが7割,11月~3月はマイナスが7割くらいに偏らせたい
		gh = gManager->LoadGraphEx("graphics/white.png");
	}
	else if (cell_gh == 15) {
		//スキル獲得マス 確率でスキルを獲得できる　リストから選ぶ　成功率が表示される
		gh = gManager->LoadGraphEx("graphics/gold.png");
	}
	else if (cell_gh == 100) {
		gh = gManager->LoadGraphEx("graphics/extraDay_1.png");
	}
	else if (cell_gh == 101) {
		gh = gManager->LoadGraphEx("graphics/extraDay_2.png");
	}


	//gh = cell_gh;
	//tScene->cell_.emplace_back(this);
	//SceneManager::m_pScene
	/*dayCell_gh[0] = LoadGraph("graphics/blue.png");
	dayCell_gh[1] = LoadGraph("graphics/red.png");
	dayCell_gh[2] = LoadGraph("graphics/white.png");
	dayCell_gh[3] = LoadGraph("graphics/gold.png");*/
}

DayCell::~DayCell()
{

}

void DayCell::Update()
{
}

void DayCell::Draw()
{
	//	DrawGraph()
	DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, gh, false);
	DrawStringEx(pos_.x-10, pos_.y - 70, -1, "%s", myDayName.c_str());
	DrawStringEx(pos_.x-50, pos_.y + 40, -1, "%s", myMonthName.c_str());
	DrawStringEx(pos_.x+30, pos_.y + 40, -1, "%d日", myDay);

	//DrawGraph(pos_.x, pos_.y, gh, false);
}


