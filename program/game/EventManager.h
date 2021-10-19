#pragma once
#include<list>
#include<vector>
#include<string>

//イベント内容を保存するクラス
class EventManager {

public:

	//std::list<EventManager*>event_;
	std::vector< std::vector<std::string> > blue_event;
	std::vector< std::vector<std::string> > red_event;
	std::vector< std::vector<std::string> > white_event;
	//std::vector< std::vector<std::string> > extra_event;

	//ゲーム実行時に一度だけ呼ぶイベントロード関数
	void loadEvent();
	//DayCellが作られるたびに呼ぶイベントセット関数
	int setEvent(int eventType);

	void DoEvent(int eventID);



};