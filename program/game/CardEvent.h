#pragma once
#include<string>
#include<vector>

class CardEvent {

public:
	/*CardEvent(int ID, int Eventtype, int Statustype, int num, std::string desc, std::string StatusName,
		int ID2, int Eventtype2, int Statustype2, int num2, std::string desc2, std::string StatusName2);*/
	CardEvent(int id,int eventType,int atk, int def, int magiatk, int magidef, int spd, int mind, int vit, std::string desc, int abiType,int abiId,int tension,int itemid);
	~CardEvent();

	
#if 0
	//eventID
	int id_ = 0;
	//0,1,2...master�Q��
	int event_type_ = 0;
	//�ω�����X�e�[�^�X
	int status_type_ = 0;
	//�ω���
	int num_ = 0;
	//����
	std::string desc_ = {};
	//�ω�����X�e�[�^�X�̖��O
	std::string StatusName_;

	//******�J�[�h�p�X�e�[�^�X*****//
	//�Q�ڂ̕ω�����X�e�[�^�X
	int event_type_second_ = 0;
	int status_type_second_ = 0;
	int num_second_ = 0;
#endif
	//eventID
	int Id = 0;
	//0,1,2...master�Q��
	int Event_type = 0;

	int Atk_Num = 0;
	int Def_Num = 0;
	int MAtk_Num = 0;
	int MDef_Num = 0;
	int Spd_Num = 0;
	int Mind_Num = 0;
	int Vit_Num = 0;

	//����
	std::string Desc = {};

	//�ǉ�����A�r���e�B�̃^�C�v -1�Ȃ�ǉ����Ȃ�
	int AbilityType = -1;
	//�ǉ�����A�r���e�B��id -1�Ȃ�ǉ����Ȃ�
	int AbilityId = -1;

	//�ω�������e���V���� -1��+2
	int Tension = 0;
	//�ǉ�����A�C�e����id -1�Ȃ�ǉ����Ȃ�
	int Item_id = -1;


	////�ω�����X�e�[�^�X�̖��O
	//std::string StatusName_second_;

	//�ω�����X�e�[�^�X�̖��O
	std::vector<std::string> changeStatusName = {};
	//�ω�����X�e�[�^�X�̗�
	std::vector<int> changeStatusValue = {};

	void run_Card_Event();

	void AddNameToVector();

};