#include "DayCell.h"
#include "DxLib.h"
#include "../library/t2klib.h"
#include "SceneManager.h"
#include "TrainingScene.h"
#include<time.h>


DayCell::DayCell(int cell_gh)
{
	//SRand(time(0));

	if (0 <= cell_gh&&cell_gh<=5) {
		//0は青マス プラス効果のイベントが発生する
		gh = LoadGraph("graphics/blue.png");
	}
	else if (6 <= cell_gh&& cell_gh <=8) {
		//1は赤マス マイナス効果のイベントが発生する
		gh = LoadGraph("graphics/red.png");
	}
	else if (9 <= cell_gh&& cell_gh<=15) {
		//2は白マス プラス効果とマイナス効果がランダムで選ばれる
		//出来れば4~10月はプラスが7割,11月~3月はマイナスが7割くらいに偏らせたい
		gh = LoadGraph("graphics/white.png");
	}


	//gh = cell_gh;
	//tScene->cell_.emplace_back(this);
	//SceneManager::m_pScene
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
	DrawRotaGraph(pos_.x, pos_.y, 1, 0, gh, false);
	//DrawGraph(pos_.x, pos_.y, gh, false);
}
