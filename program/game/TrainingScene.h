#pragma once
#include"Scene.h"
#include<list>
#include"../library/t2klib.h"

class DayCell;
class DayCard;
class EventManager;
class CharaMenuManager;
class CharaWindow;
class Chara;
class Menu;
class MenuWindow;

class TrainingScene : public BaseScene {
public:
	EventManager* eManager = nullptr;
	CharaMenuManager* cMenuManager = nullptr;

	MenuWindow* FrontMenu = nullptr;
	Menu* charaListMenu = nullptr;
	MenuWindow* charaTrainingMenu = nullptr;


	bool changeSceneFlag = false;
	int playergh[4] = {};

	//新しく一日分のセルを作る関数
	DayCell* createDayCell(int cellnum);

	//一日経過すると一つセルを消去する
	void CellDelete();

	//新しく行動カードを作る関数
	DayCard* createDayCard(int cardEventNum);

	void CardDelete();

	CharaWindow* createCharaWindow();

	//すべてのセルを入れておくリスト
	std::list<DayCell*> cell_;

	//すべてのカードを入れておくリスト
	std::list<DayCard*> card_;

	////すべてのキャラクターを入れておくリスト
	//std::list<Chara*> chara_;

	//一番左のマスの画像のx座標
	const float mass_x = 50;
	//画像間の距離(画像の大きさは50x50)
	const float mass_width = 70;

	//マス画像を表示するための中心座標
	t2k::Vector3 tbl[7] = {
		{mass_x, 70, 0},
		{mass_x + mass_width * 1, 70, 0},
		{mass_x + mass_width * 2, 70, 0},
		{mass_x + mass_width * 3, 70, 0},
		{mass_x + mass_width * 4, 70, 0},
		{mass_x + mass_width * 5, 70, 0},
		{mass_x + mass_width * 6, 70, 0},
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

	//月						1		2			3		4		5		6			7		8		9		10			11			12		
	std::string month[12] = { "火の月","水の月","地の月","風の月","雷の月","光の月","闇の月","銀の月","金の月","黄昏の月","虚無の月","明星の月" };

	//今の月
	int now_month = 2;

	std::string days[7] = { "月","火","水","木","金","土","日" };

	//一週間のどこにいるか
	int week = 0;//1~7
	//今の日
	int day = 1;//1~30


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

	//メニュー1描画シークエンス
	bool Seq_MenuDraw_1(const float deltatime);

	//メニュー2描画シークエンス
	bool Seq_MenuDraw_2(const float deltatime);

	//イベント実行シークエンス
	bool Seq_DoEvent(const float deltatime);

	bool Seq_EventFrameDraw(const float deltatime);
	//入学式イベントシークエンス
	bool Seq_NewCharactorComing(const float deltatime);
	//卒業式イベントシークエンス
	bool Seq_ExitDay(const float deltatime);

	//月始まりの強化指定イベントシークエンス
	bool Seq_SelectEnhance(const float deltatime);


	void Update();

	void Draw();    //メニュー画面、背景画像、タイトル文字の描画

private:
	int time_ = 0;
	//今のシークエンスのID
	int sequenceID = 0;
	//選択中のカードのナンバー
	int selectNum = 0;

	//0,1,2:イベント種類
	int event = 0;
	//カードのイベントid
	int size_card = 0;
	//実行イベントの残り個数
	int remainEventNum = 2;

	//表示するセルの最大数
	int cellNum = 7;
	//表示するカードの最大数
	int cardNum = 5;

	int String_Color_Black=0;
	int String_Color_Red = 0;

	int selectedCardPos = 0;
	int selectedCardEvent = 0;
	int selectedCardEventId = 0;

	int buff = 5;
	const int width = 110;

	Menu* menu_1 = nullptr;

	Menu* chara_1 = nullptr;

	//年次
	Menu* yearly = nullptr;
	//キャラ名前
	Menu* name = nullptr;
	//スタンス
	Menu* stance = nullptr;
	//レンジ
	Menu* range = nullptr;
	//ステータスの名前
	Menu* menu_3 = nullptr;
	Menu* menu_4 = nullptr;
	Menu* menu_5 = nullptr;
	Menu* menu_6 = nullptr;
	Menu* menu_7 = nullptr;
	Menu* menu_8 = nullptr;
	Menu* menu_9 = nullptr;

	//ステータスのランクと値
	Menu* menu_status_1 = nullptr;
	Menu* menu_status_2 = nullptr;
	Menu* menu_status_3 = nullptr;
	Menu* menu_status_4 = nullptr;
	Menu* menu_status_5 = nullptr;
	Menu* menu_status_6 = nullptr;
	Menu* menu_status_7 = nullptr;

	Menu* eventFrame = nullptr;
	Menu* newCharaFrame = nullptr;

	//Menu* charaListTitle = nullptr;
	int charaListTitle_gh = 0;
	int charaListName_gh = 0;

	Menu* charaListWindow = nullptr;

	MenuWindow* enhanceSelect = nullptr;

	std::string Log[9] = {};
	//ループ中か否か
	bool isnowLoop = false;
	//イベント完了フラグ→複数回実行しないためのフラグ
	bool doneEvent = false;
	//起動時に最初のイベントが走ってしまわないようにするためのフラグ
	bool doneFirstEvent = false;


	//シークエンスの列挙体
	enum class sequence {
		main,
		loop,
		doEvent,
		eventDraw,
		newChara,
		menu_1,
		menu_2,
		menu_3,
		exit,
		selectEnhance
	};
	sequence nowSeq = sequence::main;

	void addLog(std::string log);
	void LogDraw();

	void cardSelect();

	//キャラクターのステータス画面を描画する関数
	void DrawWindow();

	//キャラクターのアビリティ描画関数
	void DrawAbility(Chara* c);

	void NewCharaWindow();
	//Sequenceを移動させる関数,enumも一緒に変更する
	void ChangeSequence(sequence seq);

	void menuInit();

	


};