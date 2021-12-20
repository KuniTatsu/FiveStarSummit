#include "TrainingScene.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "DayCell.h"
#include<time.h>
#include"EventManager.h"
#include <iostream>
#include"GameManager.h"
#include"Event.h"
#include"CardEvent.h"
#include"DayCard.h"
#include"CharaMenuManager.h"
#include"CharaWindow.h"
#include"Character.h"
#include"MenuWindow.h"
#include"Ability.h"
#include"ExtraEvent.h"
#include"ForceStopDay.h"
#include"MenuWindow.h"
#include"Item.h"
//#include"AbilityManager.h"

extern GameManager* gManager;


TrainingScene::TrainingScene()
{
	saveCard.resize(5);
	eManager = new EventManager();
	cMenuManager = new CharaMenuManager();

	eventFrame = new Menu(200, 100, 500, 300, "graphics/WindowBase_02.png");
	newCharaFrame = new Menu(200, 100, 700, 500, "graphics/WindowBase_02.png");
	exitCharaFrame = new Menu(200, 100, 700, 500, "graphics/WindowBase_02.png");


	enhanceFrame = new Menu(146, 0, 650, 768, "graphics/WindowBase_02.png");
	//enhanceButton = new Menu(0, 0, 200, 100, "graphics/WindowBase_02.png");

	selectItemWindow = new Menu(146, 0, 650, 768, "graphics/WindowBase_02.png");

	MenuWindow::MenuElement_t* menu_0 = new MenuWindow::MenuElement_t[]{
		{40,50,"候補生一覧",0},
		{40,100,"訓練内容一覧",1},
		{40,150,"アイテム",2},
		{40,200,"セーブ",3},
		{40,250,"タイトルに戻る",4}
	};
	// メニューウィンドウのインスタンス化
	FrontMenu = new MenuWindow(16, 0, 130, 300, "graphics/WindowBase_02.png", menu_0, 5);

	charaListMenu = new Menu(FrontMenu->menu_x + FrontMenu->menu_width + 10, FrontMenu->menu_y, 650, 743, "graphics/WindowBase_02.png");
	cMenuManager->StatusMenuPos.x = charaListMenu->menu_x + (charaListMenu->menu_width / 2);

	MenuWindow::MenuElement_t* enhance = new MenuWindow::MenuElement_t[]{
		{735,110,"おまかせ強化",0},
		{735,160,"攻撃強化",1},
		{735,210,"防御強化",2},
		{735,260,"魔法攻撃強化",3},
		{735,310,"魔法防御強化",4},
		{735,360,"素早さ強化",5},
		{735,410,"賢さ強化",6},
		{735,460,"持久力強化",7},
	};
	enhanceSelect = new MenuWindow(900, 100, 150, 440, "graphics/WindowBase_02.png", enhance, 8);


	SRand(time(0));

	String_Color_Black = GetColor(0, 0, 0);
	String_Color_Red = GetColor(255, 0, 0);


	//プレイヤー画像のロード
	LoadDivGraph("graphics/player_chara_act_right.png", 4, 4, 1, 32, 32, playergh, false);

	charaListTitle_gh = gManager->LoadGraphEx("graphics/enhanceWindow.png");
	charaListName_gh = gManager->LoadGraphEx("graphics/charaListName.png");

	enhanceListNameGh = gManager->LoadGraphEx("graphics/charaEnhanceName.png");

	graduation_gh = gManager->LoadGraphEx("graphics/Graduation ceremony.png");

	//最初に7個リストに入れる処理を書く
	for (int k = 0; k < cellNum; ++k) {
		int random = GetRand(15);
		createDayCell(random);
	}
	for (int k = 0; k < cardNum; ++k) {
		int random = GetRand(15);
		createDayCard(random);
	}
	//Debug

	/*createCharaWindow();
	createCharaWindow();*/
	//

	//2年,3年の先輩を生成
	eManager->exEvent->NewMemberComing(3);
	eManager->exEvent->NewMemberComing(2);
}

TrainingScene::~TrainingScene()
{
	delete eManager;
}

//日程カードが選ばれるまでのシークエンス(日数移動済み)
bool TrainingScene::Seq_Training_Main(const float deltatime)
{
	//loopdaycountが0でなければシークエンスをLoopDayにする
	//loopdaycountが0になったらcell_リストの3番目のイベントを読み込む	

	if (main_sequence_.isStart()) {
		sequenceID = 0;
	}
	cardSelect();
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		FrontMenu->Open();
		//メニューをいじるシークエンスに移動する
		ChangeSequence(sequence::menu_1);
		return true;
	}
	//ループ日数を決定する所
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_NUMPAD0) && isnowLoop == false) {
		isnowLoop = true;
		doneFirstEvent = true;
		doneEvent = false;

		//現在選択中のカードの経過日数を読み込む
		//loopdaycountに代入
		int c = 0;
		for (auto card : card_) {
			if (c == selectNum)
			{
				loopdaycount = card->passedDayNum;
				passedDay = loopdaycount;

				card->isSelected = true;
				selectedCardPos = selectNum;
				selectedCardEvent = card->cardEventTypeId;
				selectedCardEventId = card->cardEventId;
			}
			c++;
		}
		CardDelete();
		addLog(std::to_string(loopdaycount) + "日経過するよ");
		//day += loopdaycount;


		int randomnum = GetRand(15);
		createDayCard(randomnum);

		//カードが持ち上がり、拡大して一定以上の大きさになると消えるシークエンスをはさみたい
		//main_sequence_.change(&TrainingScene::Seq_CardDisappear);
		ChangeSequence(sequence::loop);
		//main_sequence_.change(&TrainingScene::Seq_LoopDay);
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
			ChangeSequence(sequence::loop);
			//main_sequence_.change(&TrainingScene::Seq_LoopDay);

		}
	}
	else {
		//もし一回も移動をしていないならイベントを行わない
		if (doneFirstEvent == false)return true;
		//std::list<DayCell*>::iterator it = cell_.begin();
		//
		//++it;
		//++it;//iteratorを3番目に移動

		if (doneEvent == false) {
			std::list<DayCell*>::iterator it = cell_.begin();

			++it;
			++it;//iteratorを3番目に移動
			//今居るセルのイベントを読み込む
			event = (*it)->eventID;
			//実行するイベントの総個数→いずれ動的に変わる
			remainEventNum = 2;

			//DoEventに移動
			ChangeSequence(sequence::doEvent);
			//main_sequence_.change(&TrainingScene::Seq_DoEvent);

		}

		isnowLoop = false;

		/*if (day > 30) {
			day = 1;
			now_month = (now_month + 1) % 12;
		}*/




	}
	return true;
}

//**********************Seq_CardDisapper*****************************//
bool TrainingScene::Seq_CardDisappear(const float deltatime)
{
	//カードを大きくする
	int c = 0;
	for (auto card : card_) {
		if (c == selectNum)
		{

			if (card->isSelected == true) {
				float timecount = 0;

				while (card->exRate <= 5.0)
				{
					timecount++;
					if (timecount < 40)continue;
					card->exRate += 0.01;
					timecount = 0;

				}
			}
		}
		c++;
	}

	t2k::debugTrace("\nカードの拡大処理が終わりました\n");
	//カードを消す
	//新しくカードを生成する
	//リストに入れる
	ChangeSequence(sequence::loop);

	//main_sequence_.change(&TrainingScene::Seq_LoopDay);
	return true;
}

//**********************Seq_LoopDay**********************************//
//日程カードが選ばれたあとのシークエンス(日数移動)
bool TrainingScene::Seq_LoopDay(const float deltatime)
{

	if (main_sequence_.isStart()) {
		sequenceID = 1;

	}
	//ここにDayCellを追加したり消したりする処理を入れる
	//新しく1つDayCellを作る
	int random = GetRand(15);


	//入学式を仕込む
	if (now_month == 3 && day == 1) {
		createDayCell(100);
	}
	//卒業式を仕込む
	else if (now_month == 2 && day == 9) {
		createDayCell(101);
	}
	else {
		createDayCell(random);
	}
	std::list<DayCell*>::iterator it = cell_.begin();

	++it;
	++it;
	++it;

	//DayCell* p = new DayCell(0);
	//リストの1番をリストから外してdeleteする生成
	CellDelete();

	//もし次が必ず止まる日ならloopdaycountを0にする
	bool isForcedStopDay = false;


	for (auto stopday : eManager->ForcedStopDayList) {

		//今の日にちが必ず止まる日だったら
		if ((*it)->myMonth == stopday->month && (*it)->myDay == stopday->day) {
			loopdaycount = 0;
			//どの強制停止イベントか
			if (stopday->id == 100) {
				isForcedStopDay = true;
				doneEvent = true;
				ChangeSequence(sequence::newChara);

				//main_sequence_.change(&TrainingScene::Seq_NewCharactorComing);

				break;
			}
			else if (stopday->id == 103) {
				isForcedStopDay = true;
				doneEvent = true;
				ChangeSequence(sequence::exit);
				break;
			}
			//月始まりの日だったら一旦強化項目を選ぶシークエンスに飛ばす
			else if (stopday->id >= 900) {
				isForcedStopDay = true;

				ChangeSequence(sequence::selectEnhance);

				break;
			}
			//main_sequence_.change(&TrainingScene::Seq_NewCharactorComing);
		}

	}
	//次のフレームに移動する
	if (isForcedStopDay)return true;

	loopdaycount--;

	ChangeSequence(sequence::main);

	//main_sequence_.change(&TrainingScene::Seq_Training_Main);
	return true;
}

bool TrainingScene::Seq_MenuDraw_1(const float deltatime)
{
	if (FrontMenu->SelectNum == 0 && t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		//menuの上下を操作出来なくする
		FrontMenu->manageSelectFlag = false;

		//menu2シークエンスに移動する
		ChangeSequence(sequence::menu_2);
		return true;
	}
	else if (FrontMenu->SelectNum == 1 && t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {

		//menuの上下を操作出来なくする
		FrontMenu->manageSelectFlag = false;

		//selectEnhanceシークエンスに移動する
		ChangeSequence(sequence::selectEnhance);
		return true;
	}
	else if (FrontMenu->SelectNum == 2 && t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {

		//menuの上下を操作出来なくする
		FrontMenu->manageSelectFlag = false;

		//selectEnhanceシークエンスに移動する
		ChangeSequence(sequence::selectItem);
		return true;
	}



	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		FrontMenu->menu_live = false;
		//メインシークエンスに移動する
		ChangeSequence(sequence::main);
		return true;
	}



	return true;
}

bool TrainingScene::Seq_MenuDraw_2(const float deltatime)
{
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_UP)) {
		if (cMenuManager->StatusMenuPos.y < 75)
			cMenuManager->StatusMenuPos.y += 10;
	}
	else if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_DOWN)) {
		cMenuManager->StatusMenuPos.y -= 10;
	}

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {


		//menu1シークエンスに移動する
		FrontMenu->manageSelectFlag = true;
		cMenuManager->PosReset();
		ChangeSequence(sequence::menu_1);
		return true;
	}



	return true;
}

bool TrainingScene::Seq_DoEvent(const float deltatime)
{
	int size = 0;
	int rand_cellEvent = 0;
	//int rand_cardEvent = 0;

	//イベントを処理するシークエンス
	//イベントの画像を表示
	//イベントの内容を文章で表示
	if (main_sequence_.isStart()) {
		sequenceID = 2;
		if (event == 99) {
			rand_cellEvent = 99;
		}
		else {
			size = eManager->eventList[event].size();
			//size_card = eManager->eventList[selectedCardEvent].size();

			rand_cellEvent = GetRand(size - 1);
			//rand_cardEvent = GetRand(size_card - 1);
		}
	}

	//イベント処理シーンのウィンドウを出す
	//ウィンドウ内メッセージを読む
	//なにかのキーもしくはクリックでウィンドウが閉じる
	//このウィンドウはイベントごとに開く
	if (sequenceID == 3)return true;
	if (remainEventNum == 2) {
		//イベント1の実行処理
		t2k::debugTrace("\nセルのイベントは:%d,%d\n", event, rand_cellEvent);

		eManager->DoEvent(event, rand_cellEvent);

		sequenceID = 3;
		ChangeSequence(sequence::eventDraw);

		//main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
		return true;

	}
	else if (remainEventNum == 1) {
		//イベントの2実行処理
		t2k::debugTrace("\nカードのイベントは:%d,%d\n", selectedCardEvent, selectedCardEventId);

		eManager->DoCardEvent(selectedCardEvent, selectedCardEventId, passedDay);

		//eManager->DoEvent(selectedCardEvent, selectedCardEventId);
		sequenceID = 3;
		t2k::debugTrace("\nイベント2つめの画面処理\n");

		ChangeSequence(sequence::eventDraw);

		//main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
		return true;

	}
	//起きたイベントの内容をログで出力したい
	//Debug
	//*************cellEventのログ表示**************
	addLog("セルのイベントidは" + std::to_string(event) + ',' + std::to_string(rand_cellEvent));
	if (eManager->eventList[event][rand_cellEvent]->num_ > 0) {
		addLog(eManager->eventList[event][rand_cellEvent]->StatusName_ + "が" + std::to_string(eManager->eventList[event][rand_cellEvent]->num_) + "増加した");
	}
	else {
		int hoge = eManager->eventList[event][rand_cellEvent]->num_ * (-1);
		addLog(eManager->eventList[event][rand_cellEvent]->StatusName_ + "が" + std::to_string(hoge) + "減少した");
	}
	//*************cardEventのログ表示**************
	addLog("カードのイベントidは" + std::to_string(selectedCardEvent) + ',' + std::to_string(selectedCardEventId));

	{

		int i = 0;
		//ステータス変化があった対象リストを総なめ
		for (auto hoge : eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusName) {
			//もしその変化したステータスがプラスだったら
			if (eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusValue[i] > 0) {

				addLog(eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusName[i] + "が" +
					std::to_string(eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusValue[i]) + "増加した");
				i++;
			}
			//もしその変化したステータスがマイナスだったら
			else {
				int num = eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusValue[i] * (-1);

				addLog(eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusName[i] + "が"
					+ std::to_string(num) + "減少した");
			}
		}

	}


	//もしアビリティが追加されるイベントが実行されていたら
	if (eManager->cardEventList[selectedCardEvent][selectedCardEventId]->AbilityType != -1) {
		int abitype = eManager->cardEventList[selectedCardEvent][selectedCardEventId]->AbilityType;
		int abiid = eManager->cardEventList[selectedCardEvent][selectedCardEventId]->AbilityId;
		//どのアビリティが追加されたか名前を取得
		std::string hoge = gManager->GetAbility(abitype, abiid);
		std::string addedAbilityName = "";
		for (auto c : gManager->chara) {
			if (c->recentAddedAbility.empty())continue;
			addedAbilityName = c->recentAddedAbility;
			//うまくログ表示されない
			addLog(c->charadata->name_ + "が" + addedAbilityName + "を習得した。");
		}

	}

	doneEvent = true;

	//直近で追加されたアビリティ履歴を消去する　
	for (auto c : gManager->chara) {
		if (c->recentAddedAbility.empty()) continue;
		c->recentAddedAbility = c->recentAddedAbility.erase(0);

	}
	ChangeSequence(sequence::main);

	//main_sequence_.change(&TrainingScene::Seq_Training_Main);

	return true;
}

bool TrainingScene::Seq_EventFrameDraw(const float deltatime)
{

	//イベント1の描画処理 
	if (main_sequence_.isStart()) {

		eventFrame->menu_live = true;
	}

	eventFrame->Menu_Draw();

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		remainEventNum--;
		eventFrame->menu_live = false;

		ChangeSequence(sequence::doEvent);

		//main_sequence_.change(&TrainingScene::Seq_DoEvent);
	}

	return true;
}

bool TrainingScene::Seq_NewCharactorComing(const float deltatime)
{
	if (main_sequence_.isStart()) {
		gManager->stayYearUp();

		newCharaFrame->menu_live = true;
		eManager->exEvent->NewMemberComing(1);
		t2k::debugTrace("\n入学式イベント実行\n");
	}
	//eventframe->Menu_Draw();

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {

		newCharaFrame->menu_live = false;
		ChangeSequence(sequence::main);

		//main_sequence_.change(&TrainingScene::Seq_Training_Main);
	}

	return true;
}

bool TrainingScene::Seq_ExitDay(const float deltatime)
{
	if (main_sequence_.isStart()) {
		//3年生を卒業させる関数
		eManager->exEvent->ExitMember();
	}


	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {


		ChangeSequence(sequence::main);

	}
	return true;
}
//キャラごとの強化指定ステータスを選ぶ画面を出すシシークエンス
bool TrainingScene::Seq_SelectEnhance(const float deltatime)
{


	//キャラの枠を上下に移動させる処理
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_UP)) {
		if (cMenuManager->StatusMenuPos.y < 75)
			cMenuManager->StatusMenuPos.y += 10;
	}
	else if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_DOWN)) {
		cMenuManager->StatusMenuPos.y -= 10;
	}

	//escキーでmenu1へ戻る
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {


		//menu1シークエンスに移動する
		FrontMenu->manageSelectFlag = true;
		cMenuManager->PosReset();
		ChangeSequence(sequence::menu_1);
		return true;
	}
	//*****windowの位置変更処理*****//

	int i = 0;
	if (gManager->chara.empty() == false) {
		for (auto c : gManager->chara) {

			c->cWindow->windowPos.x = cMenuManager->StatusMenuPos.x - 20;

			c->cWindow->windowPos.y = cMenuManager->StatusMenuPos.y + (20 * (i + 1)) + ((100) * (i));
			i++;
			c->changeWindowPos(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2), c->cWindow->windowPos.y, 1);
			//ボタンの座標変更
			c->enhanceButton->menu_x = cMenuManager->StatusMenuPos.x + 130;
			c->enhanceButton->menu_y = c->cWindow->windowPos.y + 20;

			//マウスクリック検知
			if (t2k::Input::isMouseTrigger(t2k::Input::MOUSE_RELEASED_LEFT)) {
				int x; int y;
				GetMousePoint(&x, &y);
				if (x >= c->enhanceButton->menu_x && x <= c->enhanceButton->menu_x + 140
					&& y >= c->enhanceButton->menu_y && y <= c->enhanceButton->menu_y + 50) {

					DrawStringEx(100, 100, -1, "hoge");
					t2k::debugTrace("hogeee");
					////クリックされたことを取得
					//bool isClick = true;

					//今のキャラクタを取得
					nowChara = c;

					enhanceSelect->menu_live = true;

					//シークエンスを移動
					ChangeSequence(sequence::Set);
					break;

				}
			}
		}
	}
	return true;
}
//強化項目を選ぶシークエンス
bool TrainingScene::Seq_SetEnhance(const float deltatime)
{
	//enterキーを押したときのSeletNumによってキャラクタの強化項目を変更する
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		if (enhanceSelect->SelectNum == 0) {
			nowChara->charadata->myTraining = Chara::trainingAll[0];
		}
		else if (enhanceSelect->SelectNum == 1) {
			nowChara->charadata->myTraining = Chara::trainingAll[1];
		}
		else if (enhanceSelect->SelectNum == 2) {
			nowChara->charadata->myTraining = Chara::trainingAll[2];
		}
		else if (enhanceSelect->SelectNum == 3) {
			nowChara->charadata->myTraining = Chara::trainingAll[3];
		}
		else if (enhanceSelect->SelectNum == 4) {
			nowChara->charadata->myTraining = Chara::trainingAll[4];
		}
		else if (enhanceSelect->SelectNum == 5) {
			nowChara->charadata->myTraining = Chara::trainingAll[5];
		}
		else if (enhanceSelect->SelectNum == 6) {
			nowChara->charadata->myTraining = Chara::trainingAll[6];
		}
		else if (enhanceSelect->SelectNum == 7) {
			nowChara->charadata->myTraining = Chara::trainingAll[7];
		}
		//menu1シークエンスに移動する
		enhanceSelect->menu_live = false;
		ChangeSequence(sequence::selectEnhance);
		return true;
	}


	//選び終わったあと戻る処理
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {


		//menu1シークエンスに移動する
		enhanceSelect->menu_live = false;
		ChangeSequence(sequence::selectEnhance);
		return true;
	}
	return true;
}

bool TrainingScene::Seq_SelectItem(const float deltatime)
{





	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		//menu1シークエンスに移動する
		FrontMenu->manageSelectFlag = true;
		ChangeSequence(sequence::menu_1);
		return true;
	}

	return true;
}

bool TrainingScene::Seq_UseItem(const float deltatime)
{
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		//menu1シークエンスに移動する
		enhanceSelect->menu_live = false;
		ChangeSequence(sequence::selectItem);
		return true;
	}

	return true;
}

DayCell* TrainingScene::createDayCell(int cellnum) {

	//cellnum:0→青,1→赤,2→白
	DayCell* new_obj = new DayCell(cellnum);

	//DayCell自体のeventIDを決定する
	new_obj->eventID = eManager->setEvent(cellnum);
	//DayCellに自分の日にちをもたせる
	new_obj->myDayName = days[week];
	new_obj->myDay = day;
	new_obj->myMonthName = month[now_month];
	new_obj->myMonth = now_month;

	//もし日にちが特定の日にちだったら

	//ForcedStopFlagをtrueにする


	week = (week + 1) % 7;
	//日にちの更新処理
	day++;
	//日が31以上になっていたら次の月にする
	if (day > 30) {
		day = 1;
		now_month = (now_month + 1) % 12;
	}

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

DayCard* TrainingScene::createDayCard(int cardEventNum)
{
	DayCard* new_card = new DayCard(cardEventNum);
	//経過日数をランダムで決定
	int daynum = GetRand(4) + 1;
	new_card->passedDayNum = daynum;

	//カードのy座標を決定
	new_card->pos_.y = 620;

	//イベントタイプ0,1,2を決定
	new_card->cardEventTypeId = eManager->setEvent(cardEventNum);

	size_card = eManager->eventList[new_card->cardEventTypeId].size();
	//イベントタイプの中から一つをランダムで決定
	new_card->cardEventId = GetRand(size_card - 1);

	card_.emplace_back(new_card);

	return new_card;
}

void TrainingScene::CardDelete()
{
	//選択中のカードを消す
	std::list<DayCard*>::iterator it = card_.begin();
	for (auto card : card_) {
		if (card->isSelected == true)
		{
			card->is_alive_ = false;
			//std::list<DayCard*>::iterator it = card_.begin();
			for (int i = 0; i < selectedCardPos; ++i) {
				if (selectedCardPos == 0)break;
				it++;
			}
		}
	}

	card_.erase(it);
}

CharaWindow* TrainingScene::createCharaWindow()
{
	CharaWindow* new_charaWindow = new CharaWindow();
	cMenuManager->AddList(new_charaWindow);

	return new_charaWindow;
}


//シークエンスに依存しないシーン内の全般処理をここで行う
void TrainingScene::Update()
{
	main_sequence_.update(gManager->deitatime_);


	//暫定的なキャラ作成
	//if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE)) {

	//	gManager->MakeCharacter("", 1);

	//	//出力欄にメッセージ出したいんだけど出ないんだけど！
	//	//std::cout << "キャラが作成されました" << std::endl;
	//	t2k::debugTrace("\nキャラが作成されました\n");
	//}



	//--------------debug end------------------------//

	for (auto hoge : cell_) {
		if (hoge->is_alive_ == false) {
			delete hoge;
		}
	}
	for (auto hoge : card_) {
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
	int hogehoge = 0;
	for (auto card : card_) {
		card->pos_.x = cardtbl[hogehoge++].x;
		card->Draw();

	}
	//cardSelect();
	//DrawWindow();

	DrawStringEx(900, 150, -1, "%s", month[now_month].c_str());


	//------debug------
	int k = 0;
	for (auto c : cell_) {

		DrawStringEx(50, 400 + k * 50, -1, "%d", c->eventID);
		++k;
	}
	DrawStringEx(100, 300, -1, "%d", loopdaycount);


	if (nowSeq == sequence::main) {
		DrawStringEx(100, 350, -1, "SeqTrainingMain");
	}
	else if (nowSeq == sequence::loop) {
		DrawStringEx(100, 350, -1, "SeqLoopDay");
	}
	else if (nowSeq == sequence::doEvent) {
		DrawStringEx(100, 350, -1, "SeqDoEvent");
	}
	else if (nowSeq == sequence::eventDraw) {
		DrawStringEx(100, 350, -1, "SeqDrawEventFrame");
	}
	else if (nowSeq == sequence::newChara) {
		DrawStringEx(100, 350, -1, "SeqNewChara");
	}
	else if (nowSeq == sequence::menu_1) {
		DrawStringEx(100, 350, -1, "SeqMenu1");
	}
	else if (nowSeq == sequence::selectEnhance) {
		DrawStringEx(100, 350, -1, "SeqSelectEnhance");
	}

	DrawStringEx(100, 400, -1, "イベントIDは%d", eManager->eventdebugID);

	DrawRotaGraph(190, 70, 1, 0, playergh[2], true);
	//--------------------

	LogDraw();

	//cMenuManager->DrawWindow();

	//もし今のシークエンスが〇〇なら描画する
	if (nowSeq == sequence::newChara) {

		newCharaFrame->Menu_Draw();
	}
	else if (nowSeq == sequence::exit) {
		exitCharaFrame->Menu_Draw();
		DrawRotaGraph(512, 362, 1, 0, graduation_gh, true);
		DrawStringEx(300, 500, String_Color_Black, "3年生が卒業しました");

	}
	else if (nowSeq == sequence::menu_1 || nowSeq == sequence::menu_2 || nowSeq == sequence::selectEnhance || nowSeq == sequence::Set || nowSeq == sequence::selectItem) {
		FrontMenu->All();
	}

	if (nowSeq == sequence::menu_2) {
		//DrawBox(5, 5, 800, 600, -1, true);
		charaListMenu->Menu_Draw();
		DrawWindow();
		DrawStringEx(300, 300, String_Color_Black, "ここはmenu2だよ");

		DrawRotaGraph(charaListMenu->menu_x + (charaListMenu->menu_width / 2), charaListMenu->menu_y + 35, 0.5, 0, charaListTitle_gh, false);
		DrawRotaGraph(charaListMenu->menu_x + (charaListMenu->menu_width / 2), charaListMenu->menu_y + 35, 0.5, 0, charaListName_gh, true);
		//DrawStringEx(charaListMenu->menu_x + (charaListMenu->menu_width / 2), charaListMenu->menu_y + 35, String_Color_Red, "冒険者候補生一覧");
	}
	else if (nowSeq == sequence::selectEnhance || nowSeq == sequence::Set) {

		enhanceFrame->Menu_Draw();

		DrawEnhanceWindow();

		DrawRotaGraph(enhanceFrame->menu_x + (enhanceFrame->menu_width / 2), enhanceFrame->menu_y + 32, 0.43, 0, charaListTitle_gh, false);
		DrawRotaGraph(enhanceFrame->menu_x + (enhanceFrame->menu_width / 2), enhanceFrame->menu_y + 32, 0.43, 0, enhanceListNameGh, true);

		if (nowSeq == sequence::Set) {
			enhanceSelect->All();
		}
	}
	else if (nowSeq == sequence::selectItem) {
		selectItemWindow->Menu_Draw();
		int hoge = 0;
		for (int i = 0; i < gManager->haveItem.size(); ++i) {
			//通し番号i番を1個以上持っていたら
			if (gManager->haveItem[i][0] > 0) {
				if (i < 2) {
					//描画する
					DrawRotaGraph(selectItemWindow->menu_x + 10, selectItemWindow->menu_y + 10 + 50 * hoge, 2, 0, gManager->itemList[0][i]->gh, true);
					hoge += 1;
				}
				else if (2 <= i && i < 16) {
					//描画する
					DrawRotaGraph(selectItemWindow->menu_x + 10, selectItemWindow->menu_y + 10 + 50 * hoge, 2, 0, gManager->itemList[1][i - 2]->gh, true);
					hoge += 1;
				}
				else if (17 <= i && i < 38) {
					//描画する
					DrawRotaGraph(selectItemWindow->menu_x + 10, selectItemWindow->menu_y + 10 + 50 * hoge, 2, 0, gManager->itemList[2][i - 17]->gh, true);
					hoge += 1;
				}
			}
		}
	}
	////強化項目を描画,移動する処理
	//else if (nowSeq == sequence::Set) {
	//	enhanceSelect->All();


	//}


}



//7つまでログを生成する関数,古い方から消える
void TrainingScene::addLog(std::string log)
{
	if (!Log[8].empty()) {
		Log[0] = Log[1];
		Log[1] = Log[2];
		Log[2] = Log[3];
		Log[3] = Log[4];
		Log[4] = Log[5];
		Log[5] = Log[6];
		Log[6] = Log[7];
		Log[7] = Log[8];
		Log[8] = log;
		return;
	}
	for (int i = 0; i < 10; i++) {

		if (Log[i].empty()) {

			Log[i] = log;
			return;
		}
	}

}
//生成したログを表示する関数
void TrainingScene::LogDraw()
{
	for (int i = 0; i < 9; ++i) {
		DrawStringEx(100, 500 + (i * 20), -1, "%s", Log[i].c_str());
	}
}

void TrainingScene::cardSelect()
{
	//左右キーで選択中のカードを変える処理を書く

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RIGHT)) {
		selectNum = (selectNum + 1) % 5;
	}
	else if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_LEFT)) {
		selectNum = (selectNum + 4) % 5;
	}

	int c = 0;
	for (auto card : card_) {
		if (c == selectNum) {
			card->pos_.y = 600;
		}
		else {
			card->pos_.y = 620;
		}
		c++;
	}


}



void TrainingScene::DrawWindow()
{
	//Charactor* p = nullptr;

	int i = 0;
	if (gManager->chara.empty())return;
	for (auto c : gManager->chara) {

		c->cWindow->windowPos.x = cMenuManager->StatusMenuPos.x;

		c->cWindow->windowPos.y = cMenuManager->StatusMenuPos.y + (20 * (i + 1)) + ((cMenuManager->CharaWindowHeight) * (i));

		i++;

		c->changeWindowPos(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2), c->cWindow->windowPos.y, 0);
		c->charaListWindow->Menu_Draw();



		std::string name = c->charadata->name_;
		int year = c->charadata->stayYear;
		int ATK = c->charadata->ATACK;
		int DEF = c->charadata->DEFENCE;
		int MATK = c->charadata->MAGIATACK;
		int MDEF = c->charadata->MAGIDEFENCE;
		int SPEED = c->charadata->SPEED;
		int MIND = c->charadata->MIND;
		int VIT = c->charadata->VITALITY;

		int ATK_exp = c->charadata->EXP_ATACK;
		int DEF_exp = c->charadata->EXP_DEFENCE;
		int MATK_exp = c->charadata->EXP_MAGIATACK;
		int MDEF_exp = c->charadata->EXP_MAGIDEFENCE;
		int SPEED_exp = c->charadata->EXP_SPEED;
		int MIND_exp = c->charadata->EXP_MIND;
		int VIT_exp = c->charadata->EXP_VITALITY;


		std::string abi1 = {};
		//アビリティがあれば取得
		//将来的にはすべての持っているアビリティを表示させるように変更する

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 200, c->cWindow->windowPos.y + 10, String_Color_Black, "アビリティ:");


		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 10, String_Color_Black, "名前:%s", name.c_str());

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 30, String_Color_Black, "学年:%d年", year);

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 70, String_Color_Black, "攻撃力:%d", ATK);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 90, String_Color_Black, "防御力:%d", DEF);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 110, String_Color_Black, "魔法攻撃力:%d", MATK);

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 130, String_Color_Black, "魔法防御力:%d", MDEF);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 150, String_Color_Black, "速度:%d", SPEED);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 170, String_Color_Black, "賢さ:%d", MIND);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 190, String_Color_Black, "持久力:%d", VIT);

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 50, String_Color_Black, "攻撃力経験値:%d", ATK_exp);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 70, String_Color_Black, "防御力経験値:%d", DEF_exp);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 90, String_Color_Black, "魔攻撃力経験値:%d", MATK_exp);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 110, String_Color_Black, "魔防御力:%d", MDEF_exp);


		//DrawGraph(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 50, c->cWindow->windowPos.y + 10, c->gh[2], false);
		DrawRotaGraph(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 170, c->cWindow->windowPos.y + 20, 1, 0, c->gh[1], true);

		DrawAbility(c);


	}

}

void TrainingScene::DrawEnhanceWindow()
{
	//int i = 0;
	if (gManager->chara.empty())return;
	for (auto c : gManager->chara) {


		//キャラクターごとのウィンドウ描画
		c->charaEnhanceWindow->Menu_Draw();

		//DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 20, String_Color_Black, "名前:%s", c->charadata->name_.c_str());
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 20, String_Color_Black, "名前:%s", c->charadata->name_.c_str());
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 40, String_Color_Black, "攻撃");
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 60, c->cWindow->windowPos.y + 40, String_Color_Black, "防御");
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 110, c->cWindow->windowPos.y + 40, String_Color_Black, "魔法攻撃");
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 180, c->cWindow->windowPos.y + 40, String_Color_Black, "魔法防御");
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 240, c->cWindow->windowPos.y + 40, String_Color_Black, "素早さ");
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 300, c->cWindow->windowPos.y + 40, String_Color_Black, "精神力");
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 360, c->cWindow->windowPos.y + 40, String_Color_Black, "持久力");

		//キャラクターのステータスと評価を表示する





		//キャラクターウィンドウごとのボタン描画
		c->enhanceButton->Menu_Draw();

		//強化中の項目を表示
		DrawStringEx(c->enhanceButton->menu_x + 10, c->enhanceButton->menu_y + 20, String_Color_Black, "強化中:%s", c->charadata->myTraining.c_str());


	}
}

void TrainingScene::DrawAbility(Chara* c)
{
	if (c->charadata->Ability.empty() == false) {

		int i = 0;
		for (auto abi : c->charadata->Ability) {

			DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 300, c->cWindow->windowPos.y + 10 + (20 * i),
				String_Color_Black, "%s", abi->ability_name.c_str());
			++i;
		}
	}


}

void TrainingScene::NewCharaWindow()
{
	eventFrame->Menu_Draw();

}

void TrainingScene::ChangeSequence(sequence seq)
{
	nowSeq = seq;
	if (seq == sequence::main) {
		main_sequence_.change(&TrainingScene::Seq_Training_Main);
	}
	else if (seq == sequence::loop) {
		main_sequence_.change(&TrainingScene::Seq_LoopDay);
	}
	else if (seq == sequence::doEvent) {
		main_sequence_.change(&TrainingScene::Seq_DoEvent);
	}
	else if (seq == sequence::eventDraw) {
		main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
	}
	else if (seq == sequence::newChara) {
		main_sequence_.change(&TrainingScene::Seq_NewCharactorComing);
	}
	else if (seq == sequence::menu_1) {
		main_sequence_.change(&TrainingScene::Seq_MenuDraw_1);
	}
	else if (seq == sequence::menu_2) {
		main_sequence_.change(&TrainingScene::Seq_MenuDraw_2);
	}
	else if (seq == sequence::exit) {
		main_sequence_.change(&TrainingScene::Seq_ExitDay);
	}
	else if (seq == sequence::selectEnhance) {
		main_sequence_.change(&TrainingScene::Seq_SelectEnhance);
	}
	else if (seq == sequence::Set) {
		main_sequence_.change(&TrainingScene::Seq_SetEnhance);
	}
	else if (seq == sequence::selectItem) {
		main_sequence_.change(&TrainingScene::Seq_SelectItem);
	}
	else if (seq == sequence::useItem) {
		main_sequence_.change(&TrainingScene::Seq_UseItem);
	}

}

void TrainingScene::menuInit()
{
	menu_1 = new Menu(10, 10, 1010, 700, "graphics/WindowBase_02.png");
	chara_1 = new Menu(menu_1->menu_x + 10, menu_1->menu_y + 10, 990, 150, "graphics/WindowBase_01.png");

	yearly = new Menu(chara_1->menu_x + 10, chara_1->menu_y + 85, 55, 60, "graphics/WindowBase_01.png");

	name = new Menu(chara_1->menu_x + 10, chara_1->menu_y + 10, 165, 70, "graphics/WindowBase_01.png");

	stance = new Menu(yearly->menu_x + 55, chara_1->menu_y + 85, 55, 60, "graphics/WindowBase_01.png");

	range = new Menu(yearly->menu_x + 110, chara_1->menu_y + 85, 55, 60, "graphics/WindowBase_01.png");


	//能力値の名前の枠
	menu_3 = new Menu(range->menu_x + 60, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_4 = new Menu(menu_3->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_5 = new Menu(menu_4->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_6 = new Menu(menu_5->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_7 = new Menu(menu_6->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_8 = new Menu(menu_7->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_9 = new Menu(menu_8->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");


	menu_status_1 = new Menu(menu_3->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_2 = new Menu(menu_4->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_3 = new Menu(menu_5->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_4 = new Menu(menu_6->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_5 = new Menu(menu_7->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_6 = new Menu(menu_8->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_7 = new Menu(menu_9->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
}

void TrainingScene::CharaSpeak()
{
	//ランダムに3人を今の在籍Memberから選ぶ
	//選んだキャラクタをlistにいれる
	//リストの中にいるキャラクターをアニメーションさせる(喋らせる？)

	//毎フレーム回して条件にハマれば吹き出しを出してメッセージを表示する
	//メッセージ表示は秒数で管理する
	//n秒たったら吹き出しを消す

	//吹き出しと中のメッセージは一つのクラスで作るべき？


}

void TrainingScene::LoadCreateCard(int EventType, int EventNum, int PassedDay)
{
	//カードの持つイベントを指定して生成
	DayCard* new_card = new DayCard(EventType, EventNum);
	//経過日数を設定
	new_card->passedDayNum = PassedDay;

	card_.emplace_back(new_card);
}
//EventType:0→15,100,101
void TrainingScene::LoadCreateCell(int EventType)
{
	//cellnum:0→青,1→赤,2→白
	DayCell* new_obj = new DayCell(EventType);
	//DayCell自体のeventIDを決定する
	new_obj->eventID = eManager->setEvent(EventType);

	//DayCellに自分の日にちをもたせる
	new_obj->myDayName = days[week];
	new_obj->myDay = day;
	new_obj->myMonthName = month[now_month];
	new_obj->myMonth = now_month;

	//日にちの更新処理
	day++;
	//日が31以上になっていたら次の月にする
	if (day > 30) {
		day = 1;
		now_month = (now_month + 1) % 12;
	}

	cell_.emplace_back(new_obj);
}

void TrainingScene::Save()
{
	//card
	//int EventType, int EventNum, int PassedDay
	//すべてのカードの上の3つを取得する
	int i = 0;
	for (auto haveCard : card_) {
		int type = haveCard->cardEventTypeId;
		int id = haveCard->cardEventId;
		int day = haveCard->passedDayNum;

		saveCard[i].emplace_back(type);
		saveCard[i].emplace_back(id);
		saveCard[i].emplace_back(day);
		++i;
	}


	//cell
	//EventType
	//day,week,now_month



	FILE* fp = nullptr;
	fopen_s(&fp, "saveData/test.bin", "wb");

	fwrite(saveCard[0].data(), saveCard[0].size(), 1, fp);
	fwrite("\n", 1, 1, fp);
	fwrite(saveCard[1].data(), saveCard[0].size(), 1, fp);
	fwrite("\n", 1, 1, fp);
	fwrite(saveCard[2].data(), saveCard[0].size(), 1, fp);
	fwrite("\n", 1, 1, fp);



	int buff[5] = { 10,20,30,40,50 };
	//sprintf_s(buff, "あいうえお\n\0");
	fwrite(buff, sizeof(buff), 1, fp);
	fclose(fp);

}

void TrainingScene::Load()
{


}