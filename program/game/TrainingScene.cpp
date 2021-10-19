#include "TrainingScene.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "DayCell.h"
#include<time.h>
#include"EventManager.h"
#include <iostream>
#include"GameManager.h"

extern GameManager* gManager;


TrainingScene::TrainingScene()
{
	eManager = new EventManager();

	SRand(time(0));

	//最初に7個リストに入れる処理を書く
	for (int k = 0; k < 7; ++k) {
		int random = GetRand(2);
		createDayCell(random);
	}
}

TrainingScene::~TrainingScene()
{
}

//日程カードが選ばれるまでのシークエンス(日数移動済み)
bool TrainingScene::Seq_Training_Main(const float deltatime)
{
	//loopdaycountが0でなければシークエンスをLoopDayにする
	//loopdaycountが0になったらcell_リストの3番目のイベントを読み込む	todo :DayCellにイベントidをもたせる,イベントidを読んで実行する関数を作る
	//	→3番目にプレイヤーを常に置くため

	if (loopdaycount != 0) {
		main_sequence_.change(&TrainingScene::Seq_Training_Main);
	}
	else {

		std::list<DayCell*>::iterator it = cell_.begin();
		//it += 2;　できない
		++it;
		++it;//iteratorを3番目に移動
		//イベントIDを取得
		//考えること:どこで実際に実行されるイベントを決定するか
			// ○1:newしたときにcellの色によってイベントリストが決まり、ランダムでイベントが設定される
			//   2:loopdaycountが0になったときに色を取得してイベントリストを決め、ランダムでイベントを設定する

		int event = (*it)->eventID;
		//イベント実行関数->どこに置くか考え中
		// DoEvent(event);
	}


	return true;
}

//日程カードが選ばれたあとのシークエンス(日数移動)
bool TrainingScene::Seq_LoopDay(const float deltatime)
{
	//ここにDayCellを追加したり消したりする処理を入れる


	return true;
}

DayCell* TrainingScene::createDayCell(int cellnum) {

	//cellnum:0→青,1→赤,2→白
	DayCell* new_obj = new DayCell(cellnum);

	int eventType = 0;

	if (cellnum == 0) {
		eventType = GetRand(3);
	}
	else if (cellnum == 1) {
		eventType = GetRand(3) + 4;
	}
	else if (cellnum == 2) {
		eventType = GetRand(3) + 8;
	}

	//eManager->setEvent(eventType);

	//DayCell自体のeventIDを決定する
	new_obj->eventID = eManager->setEvent(eventType);

	cell_.emplace_back(new_obj);
	return new_obj;
}

void TrainingScene::CellDelete()
{
	//リストの1番目のcellをリストから外す
	//cell_.pop_front();

	std::list<DayCell*>::iterator it = cell_.begin();
	(*it)->is_alive_ = false;
	cell_.erase(it);
}



void TrainingScene::Update()
{
	//本来はカードを選ぶ->カードの進行日数が決まる->変数に代入->シーケンス変数が0になるまで止まるシーケンス→動くシーケンス→止まるシーケンスを繰り返す
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		//新しく1つDayCellを作る
		int random = GetRand(2);
		createDayCell(random);
		//DayCell* p = new DayCell(0);
		//リストの1番をリストから外してdeleteする生成
		CellDelete();
	}

	//暫定的なキャラ作成
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE)) {

		gManager->MakeCharacter();
		std::cout << "キャラが作成されました" << std::endl;
	}


	for (auto hoge : cell_) {
		if (hoge->is_alive_ == false) {
			delete hoge;
		}
	}


}

void TrainingScene::Draw()
{
	int i = 0;
	for (auto cell : cell_) {
		cell->pos_ = tbl[i++];
		cell->Draw();
	}
	//------debug------
	for (auto c : cell_) {
		int i = 0;
		DrawStringEx(100, 400 + i * 50, -1, "%d", c->eventID);
	}


}
