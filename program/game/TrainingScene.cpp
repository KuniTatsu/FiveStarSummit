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

	LoadDivGraph("graphics/player_chara_act_right.png", 4, 4, 1, 32, 32, playergh, false);

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

	if (main_sequence_.isStart()) {
		sequenceID = 0;
	}

#if 0
	if (isnowLoop == false) {
		DrawStringEx(200, 500, -1, "日数を入力してね");
		std::cin >> loopdaycount;

		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
			main_sequence_.change(&TrainingScene::Seq_LoopDay);
			isnowLoop = true;
		}
	}

#endif

	//ループ日数を決定する所
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN) && isnowLoop == false) {
		isnowLoop = true;
		doneEvent = false;
		//経過させる日数を出す
		loopdaycount = GetRand(4) + 1;//一時的に1~5日の間で経過日数が決まるように設定
		main_sequence_.change(&TrainingScene::Seq_LoopDay);
		return true;
	}


	//DrawStringEx(200, 350, -1, "Seq_Training_Main");
	//ループ日数決定後にループが開始し、0になるまでここが回る
	if (loopdaycount != 0)
	{
		//一日経過する間隔
		time_++;
		if (time_ > 40) {
			time_ = 0;
			main_sequence_.change(&TrainingScene::Seq_LoopDay);

		}
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
		//今は何回も呼ばれてしまうので一回だけ呼ばれるように変更する
			//シークエンスをもう一つ作るか、bool型変数で制御するか
			//debugではbool型で制御する
		if (doneEvent == false) {
			eManager->DoEvent(event);
			doneEvent = true;
		}

		////ループ日数を決定する所
		//if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {

		//	//経過させる日数を出す
		//	loopdaycount = GetRand(4) + 1;//一時的に1~5日の間で経過日数が決まるように設定
		//	main_sequence_.change(&TrainingScene::Seq_LoopDay);
		//}
		isnowLoop = false;
	}
	return true;
}

//日程カードが選ばれたあとのシークエンス(日数移動)
bool TrainingScene::Seq_LoopDay(const float deltatime)
{

	if (main_sequence_.isStart()) {
		sequenceID = 1;
	}
	//ここにDayCellを追加したり消したりする処理を入れる
	//新しく1つDayCellを作る
	int random = GetRand(2);
	createDayCell(random);
	//DayCell* p = new DayCell(0);
	//リストの1番をリストから外してdeleteする生成
	CellDelete();
	loopdaycount--;
	main_sequence_.change(&TrainingScene::Seq_Training_Main);
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
	//ここいる？？？？？？？？
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


//シークエンスに依存しないシーン内の全般処理をここで行う
void TrainingScene::Update()
{
	main_sequence_.update(gManager->deitatime_);
	//--------------debug------------------------//

#if 0
	//本来はカードを選ぶ->カードの進行日数が決まる->変数に代入->シーケンス変数が0になるまで止まるシーケンス→動くシーケンス→止まるシーケンスを繰り返す
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		//新しく1つDayCellを作る
		int random = GetRand(2);
		createDayCell(random);
		//DayCell* p = new DayCell(0);
		//リストの1番をリストから外してdeleteする生成
		CellDelete();
	}
#endif

	//暫定的なキャラ作成
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE)) {

		gManager->MakeCharacter();
		//出力欄にメッセージ出したいんだけど出ないんだけど！
		std::cout << "キャラが作成されました" << std::endl;
	}

	//--------------debugend------------------------//

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
	int k = 0;
	for (auto c : cell_) {

		DrawStringEx(100, 400 + k * 50, -1, "%d", c->eventID);
		++k;
	}
	DrawStringEx(200, 300, -1, "%d", loopdaycount);
	//if(main_sequence_==&TrainingScene::Seq_Training_Main)
	//現在のシークエンスをif分で評価したい
	if (sequenceID == 0) {
		DrawStringEx(200, 350, -1, "SeqTrainingMain");
	}
	else {
		DrawStringEx(200, 350, -1, "SeqLoopDay");
	}

	DrawStringEx(200, 400, -1, "イベントIDは%d", eManager->eventdebugID);

}
