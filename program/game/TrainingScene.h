#pragma once
#include"Scene.h"
#include<list>
#include"../library/t2klib.h"

class DayCell;
class DayCard;
class EventManager;

class TrainingScene : public BaseScene {
public:
	EventManager* eManager = nullptr;



	bool changeSceneFlag = false;
	int playergh[4] = {};

	//新しく一日分のセルを作る関数
	DayCell* createDayCell(int cellnum);

	//一日経過すると一つセルを消去する
	void CellDelete();

	//新しく行動カードを作る関数
	DayCard* createDayCard(int cardEventNum);

	//すべてのセルを入れておくリスト
	std::list<DayCell*> cell_;

	//すべてのカードを入れておくリスト
	std::list<DayCard*> card_;

	//一番左のマスの画像のx座標
	const float mass_x = 50;
	//画像間の距離(画像の大きさは50x50)
	const float mass_width = 70;

	//マス画像を表示するための中心座標
	t2k::Vector3 tbl[7] = {
		{mass_x, 50, 0},
		{mass_x + mass_width * 1, 50, 0},
		{mass_x + mass_width * 2, 50, 0},
		{mass_x + mass_width * 3, 50, 0},
		{mass_x + mass_width * 4, 50, 0},
		{mass_x + mass_width * 5, 50, 0},
		{mass_x + mass_width * 6, 50, 0},
	};
	//カードの一番左の画像のx座標
	const float card_x = 400;
	//画像感の距離(画像の大きさは40x80)
	const float card_width = 120;

	//カードを表示するための中心座標
	t2k::Vector3 cardtbl[5] = {
		{card_x, 620, 0},
		{card_x + card_width * 1, 620, 0},
		{card_x + card_width * 2, 620, 0},
		{card_x + card_width * 3, 620, 0},
		{card_x + card_width * 4, 620, 0},

	};

	//初期シークエンスを設定
	t2k::Sequence<TrainingScene*> main_sequence_ =
		t2k::Sequence<TrainingScene*>(this, &TrainingScene::Seq_Training_Main);

	TrainingScene();
	~TrainingScene();

	//メインシークエンス 各処理へ移行する
	bool Seq_Training_Main(const float deltatime);

	//選択したカードが消えるまでのシークエンス
	bool Seq_CardDisappear(const float deltatime);


	//日数経過中のシークエンス ループカウントが0になるまで繰り返す ループカウント:経過日数
	bool Seq_LoopDay(const float deltatime);

	int loopdaycount = 0;




	void Update();

	void Draw();    //メニュー画面、背景画像、タイトル文字の描画

private:
	int time_ = 0;
	int sequenceID = 0;
	int selectNum = 0;

	int cellNum = 7;
	int cardNum = 5;

	std::string Log[9] = {};
	//ループ中か否か
	bool isnowLoop = false;
	//イベント完了フラグ→複数回実行しないためのフラグ
	bool doneEvent = false;
	//起動時に最初のイベントが走ってしまわないようにするためのフラグ
	bool doneFirstEvent = false;

	void addLog(std::string log);
	void LogDraw();

	void cardSelect();

};