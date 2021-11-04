#include "DayCard.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"

DayCard::DayCard(int randomNum)
{

	gh = LoadGraph("graphics/dayCard.png");
	Color = GetColor(255, 0, 0);
}

DayCard::~DayCard()
{
}

void DayCard::Update()
{

}

void DayCard::Draw()
{
	//行動カードを指定枚数分並べて表示する

	//選択中(カーソルがあっている)の行動カードの枠をハイライトする
	//出来れば点滅させたい
	//選択中の行動カードのy座標を他よりも少し上に移動させる

	//通常のカード表示
	DrawRotaGraph(pos_.x, pos_.y, exRate, 0, gh, false);
	
	DrawStringEx(pos_.x + initpos.x, pos_.y + initpos.y, Color, "%d", passedDayNum);
	
}
