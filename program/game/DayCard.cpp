#include "DayCard.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"
#include "GameManager.h"

extern GameManager* gManager;
//0~15
DayCard::DayCard(int randomNum)
{

	//gh = LoadGraph("graphics/dayCard.png");
	Color = GetColor(255, 0, 0);
}

DayCard::DayCard(int EventType, int EventId)
{
	cardEventTypeId = EventType;
	cardEventId = EventId;

	//どのイベントを持っているかで画像を変える
	gh = LoadGraph("graphics/dayCard.png");
	Color = GetColor(255, 0, 0);


}

DayCard::~DayCard()
{
}

void DayCard::setGh(int eventType, int eventId)
{
	if (eventType == 0 && eventId == 0) {
		gh=gManager->LoadGraphEx("graphics/card/dayCard_0_0.png");
	}
	else if (eventType == 0 && eventId == 1) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_0_1.png");
	}
	else if (eventType == 0 && eventId == 2) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_0_2.png");
	}
	else if (eventType == 0 && eventId == 3) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_0_3.png");
	}
	else if (eventType == 0 && eventId == 4) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_0_4.png");
	}
	else if (eventType == 0 && eventId == 5) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_0_5.png");
	}
	else if (eventType == 0 && eventId == 6) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_0_6.png");
	}
	else if (eventType == 1 && eventId == 0) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_1_0.png");
	}
	else if (eventType == 1 && eventId == 1) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_1_1.png");
	}
	else if (eventType == 1 && eventId == 2) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_1_2.png");
	}
	else if (eventType == 1 && eventId == 3) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_1_3.png");
	}
	else if (eventType == 1 && eventId == 4) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_1_4.png");
	}
	else if (eventType == 1 && eventId == 5) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_1_5.png");
	}
	else if (eventType == 1 && eventId == 6) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_1_6.png");
	}
	else if (eventType == 2) {
		gh = gManager->LoadGraphEx("graphics/card/dayCard_2_1.png");
	}
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
	/*DrawStringEx(pos_.x + initpos.x, pos_.y + initpos.y + 20, Color, "イベントid:");

	DrawStringEx(pos_.x + initpos.x, pos_.y + initpos.y + 40, Color, "%d", cardEventTypeId);*/

}
