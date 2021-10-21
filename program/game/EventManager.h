#pragma once
#include<list>
#include<vector>
#include<string>

class Event;

//イベント内容を保存するクラス
class EventManager {

public:

	EventManager();

	//std::list<EventManager*>event_;
	/*
	std::vector< std::vector<std::string> > blue_event;
	std::vector< std::vector<std::string> > red_event;
	std::vector< std::vector<std::string> > white_event;
	//std::vector< std::vector<std::string> > extra_event;
	*/

	std::vector< std::vector<std::string> > event_all;
	std::vector<std::vector<Event*> >eventList;




	//ゲーム実行時に一度だけ呼ぶイベントロード関数
	void loadEvent();
	//DayCellが作られるたびに呼ぶイベントセット関数
	int setEvent(int eventType);


	//0→ステータス上昇,
	//1→やる気パラメータup,
	//2→特殊能力獲得
	//3→アイテム獲得
	//...
	void DoEvent(int eventID,int randomnum);

	int eventdebugID = 0;
private:
	int Random(int rangeMax);






};