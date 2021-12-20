#pragma once
#include"../library/t2klib.h"


class DayCard {

public:

	DayCard(int randomNum);
	DayCard(int EventType,int EventId);
	~DayCard();

	//カードの画面内の位置
	t2k::Vector3 pos_;

	//カードの大きさ
	const int CardWidth = 100;
	const int CardHeight = 120;

	double exRate = 1;

	unsigned int Color = 0;

	//カードの中の数字の場所を決めるvector
	const t2k::Vector3 initpos = { -40, -50, 0 };

	//経過日数
	int passedDayNum = 0;

	//カードを使ったときに起こるイベントのtypeid
	int cardEventTypeId = 0;

	int cardEventId = 0;

	

	//カード生存フラグ
	bool is_alive_ = true;
	//選ばれたフラグ
	bool isSelected = false;

	void Update();
	void Draw();

private:

	//グラフィックハンドル
	int gh = 0;


};