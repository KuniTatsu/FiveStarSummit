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
//#include"AbilityManager.h"

extern GameManager* gManager;


TrainingScene::TrainingScene()
{
	eManager = new EventManager();
	cMenuManager = new CharaMenuManager();


	SRand(time(0));

	String_Color_Black = GetColor(0, 0, 0);


	//プレイヤー画像のロード
	LoadDivGraph("graphics/player_chara_act_right.png", 4, 4, 1, 32, 32, playergh, false);

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
				card->isSelected = true;
				selectedCardPos = selectNum;
				selectedCardEvent = card->cardEventTypeId;
				selectedCardEventId = card->cardEventId;
			}
			c++;
		}
		CardDelete();
		addLog(std::to_string(loopdaycount) + "日経過するよ");
		day += loopdaycount;


		int randomnum = GetRand(15);
		createDayCard(randomnum);

		//カードが持ち上がり、拡大して一定以上の大きさになると消えるシークエンスをはさみたい
		//main_sequence_.change(&TrainingScene::Seq_CardDisappear);
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
			main_sequence_.change(&TrainingScene::Seq_DoEvent);
			//eventIDは0,1,2

			//int size = eManager->eventList[event].size();

			//int rand_cellEvent = GetRand(size - 1);
			//int rand_cardEvent = GetRand(size - 1);

			//eManager->DoEvent(event, rand_cellEvent);
			//eManager->DoEvent(selectedCardEvent, rand_cardEvent);
			//addLog("カードのイベントidは" + std::to_string(selectedCardEvent) + ',' + std::to_string(rand_cardEvent));

			////起きたイベントの内容をログで出力したい
			////Debug
			////*************cellEventのログ表示**************
			//if (eManager->eventList[event][rand_cellEvent]->num_ > 0) {
			//	addLog(eManager->eventList[event][rand_cellEvent]->StatusName_ + "が" + std::to_string(eManager->eventList[event][rand_cellEvent]->num_) + "増加した");
			//}
			//else {
			//	int hoge = eManager->eventList[event][rand_cellEvent]->num_ * (-1);
			//	addLog(eManager->eventList[event][rand_cellEvent]->StatusName_ + "が" + std::to_string(hoge) + "減少した");
			//}
			////*************cardEventのログ表示**************
			//if (eManager->eventList[event][rand_cardEvent]->num_ > 0) {
			//	addLog(eManager->eventList[event][rand_cardEvent]->StatusName_ + "が" + std::to_string(eManager->eventList[event][rand_cardEvent]->num_) + "増加した");
			//}
			//else {
			//	int hoge = eManager->eventList[event][rand_cardEvent]->num_ * (-1);
			//	addLog(eManager->eventList[event][rand_cardEvent]->StatusName_ + "が" + std::to_string(hoge) + "減少した");
			//}

			//doneEvent = true;
		}

		isnowLoop = false;

		if (day > 30) {
			day = 1;
			now_month = (now_month + 1) % 12;
		}

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

	main_sequence_.change(&TrainingScene::Seq_LoopDay);
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
	createDayCell(random);
	//DayCell* p = new DayCell(0);
	//リストの1番をリストから外してdeleteする生成
	CellDelete();
	loopdaycount--;
	main_sequence_.change(&TrainingScene::Seq_Training_Main);
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
		size = eManager->eventList[event].size();
		//size_card = eManager->eventList[selectedCardEvent].size();

		rand_cellEvent = GetRand(size - 1);
		//rand_cardEvent = GetRand(size_card - 1);
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
		main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
		return true;

	}
	else if (remainEventNum == 1) {
		//イベントの2実行処理
		t2k::debugTrace("\nカードのイベントは:%d,%d\n", selectedCardEvent, selectedCardEventId);

		eManager->DoCardEvent(selectedCardEvent, selectedCardEventId);

		//eManager->DoEvent(selectedCardEvent, selectedCardEventId);
		sequenceID = 3;
		t2k::debugTrace("\nイベント2つめの画面処理\n");

		main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
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

	main_sequence_.change(&TrainingScene::Seq_Training_Main);

	return true;
}

bool TrainingScene::Seq_EventFrameDraw(const float deltatime)
{

	//イベント1の描画処理 
	if (main_sequence_.isStart()) {
		eventframe = new Menu(200, 100, 500, 300, "graphics/WindowBase_02.png");
		eventframe->menu_live = true;
	}

	eventframe->Menu_Draw();

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		remainEventNum--;
		eventframe->menu_live = false;
		delete eventframe;
		main_sequence_.change(&TrainingScene::Seq_DoEvent);
	}

	return true;
}

DayCell* TrainingScene::createDayCell(int cellnum) {

	//cellnum:0→青,1→赤,2→白
	DayCell* new_obj = new DayCell(cellnum);

	//DayCell自体のeventIDを決定する

	new_obj->eventID = eManager->setEvent(cellnum);
	new_obj->myday = days[week];
	week = (week + 1) % 7;

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
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE)) {

		gManager->MakeCharacter();

		//出力欄にメッセージ出したいんだけど出ないんだけど！
		//std::cout << "キャラが作成されました" << std::endl;
		t2k::debugTrace("\nキャラが作成されました\n");
	}

	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_UP)) {
		if (cMenuManager->StatusMenuPos.y > 15)return;
		cMenuManager->StatusMenuPos.y += 10;
	}
	else if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_DOWN)) {
		cMenuManager->StatusMenuPos.y -= 10;
	}

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
	DrawWindow();

	DrawStringEx(900, 150, -1, "%s", month[now_month].c_str());


	//------debug------
	int k = 0;
	for (auto c : cell_) {

		DrawStringEx(50, 400 + k * 50, -1, "%d", c->eventID);
		++k;
	}
	DrawStringEx(100, 300, -1, "%d", loopdaycount);

	if (sequenceID == 0) {
		DrawStringEx(100, 350, -1, "SeqTrainingMain");
	}
	else if (sequenceID == 1) {
		DrawStringEx(100, 350, -1, "SeqLoopDay");
	}
	else if (sequenceID == 2) {
		DrawStringEx(100, 350, -1, "SeqDoEvent");
	}

	DrawStringEx(100, 400, -1, "イベントIDは%d", eManager->eventdebugID);

	DrawRotaGraph(190, 70, 1, 0, playergh[2], true);
	//--------------------

	LogDraw();

	cMenuManager->DrawWindow();

	//もし今のシークエンスが〇〇なら描画する


		//if (gManager->isInput== true) {
		//	//入力モードの描画
		//	DrawKeyInputModeString(640, 480);

		//	//入力途中の文字列の描画
		//	DrawKeyInputString(0, 0, gManager->InputHandle);
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

		c->cWindow->windowPos.y = cMenuManager->StatusMenuPos.y + (20 * (i + 1)) + ((cMenuManager->CharaWindowHeight) * (i));;

		i++;
		DrawBox(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2), c->cWindow->windowPos.y,
			c->cWindow->windowPos.x + (cMenuManager->CharaWindowWidth / 2), c->cWindow->windowPos.y + cMenuManager->CharaWindowHeight, -1, true);

		std::string name = c->charadata->name_;
		int ATK = c->charadata->ATACK;
		int DEF = c->charadata->DEFENCE;
		int MATK = c->charadata->MAGIATACK;
		int MDEF = c->charadata->MAGIDEFENCE;
		int SPEED = c->charadata->SPEED;
		int MIND = c->charadata->MIND;
		int VIT = c->charadata->VITALITY;
		std::string abi1 = {};
		//アビリティがあれば取得
		//将来的にはすべての持っているアビリティを表示させるように変更する
		if (c->charadata->Ability.empty() == false) {
			abi1 = c->charadata->Ability[0]->ability_name;
			DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 70, c->cWindow->windowPos.y + 10, String_Color_Black, "アビリティ:", abi1);
		}

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 10, String_Color_Black, "名前:%s", name.c_str());
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 50, String_Color_Black, "攻撃力:%d", ATK);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 70, String_Color_Black, "防御力:%d", DEF);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 90, String_Color_Black, "魔法攻撃力:%d", MATK);

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 110, String_Color_Black, "魔法防御力:%d", MDEF);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 130, String_Color_Black, "速度:%d", SPEED);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 150, String_Color_Black, "賢さ:%d", MIND);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 170, String_Color_Black, "持久力:%d", VIT);




		DrawAbility(c);
	}

}

void TrainingScene::DrawAbility(Chara* c)
{



}

