#pragma once
#include<string>
#include<vector>

class GameManager;

//������~���̃C�x���g�Ȃ�
class ExtraEvent {

public:
	ExtraEvent();

	

	//���w���C�x���g
	void NewMemberComing();

	//���Ǝ��C�x���g
	void ExitMember();

	void loadCharaRandomName();
	std::vector< std::vector<std::string> >RandomName_All;

	std::vector < std::string> RandomNameList;



};