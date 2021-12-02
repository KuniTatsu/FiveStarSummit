#pragma once
#include<string>
#include<vector>

class GameManager;

//強制停止日のイベントなど
class ExtraEvent {

public:
	ExtraEvent();



	//入学式イベント
	void NewMemberComing();

	//卒業式イベント
	void ExitMember();

	void loadCharaRandomName();
	std::vector< std::vector<std::string> >RandomName_All;

	std::vector < std::string> RandomNameList;

private:
	std::vector<std::string>usedNameList;

	std::string ChooseName();


};
