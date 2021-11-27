#pragma once
#include<list>
#include<vector>
#include<string>

class Event;
class CardEvent;

//イベント内容を保存するクラス
class EventManager {

public:

	EventManager();



	std::vector< std::vector<std::string> > event_all;
	//読み込んだイベントを格納するvector
	std::vector<std::vector<Event*> >eventList;

	//ゲーム実行時に一度だけ呼ぶイベントロード関数
	void loadEvent();
	//DayCellが作られるたびに呼ぶイベントセット関数
	int setEvent(int eventType);


	std::vector< std::vector<std::string> > cardEvent_all;

	std::vector<std::vector<CardEvent*>> cardEventList;

	//ゲーム実行時に一度だけ呼ぶイベントロード関数
	void loadCardEvent();


	//0→ステータス上昇,いいイベント
	//1→ステータス上昇,わるいイベント
	//2→ステータス上昇,ランダムイベント
	//3→複合ステータスイベント(カード用)
	void DoEvent(int eventID, int randomnum);
	//いずれ追加する
	//1→やる気パラメータup,
	//2→特殊能力獲得
	//3→アイテム獲得

	void DoCardEvent(int eventType,int eventId);



	int eventdebugID = 0;
private:
	int Random(int rangeMax);






};