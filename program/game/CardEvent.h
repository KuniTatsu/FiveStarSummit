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
	//0,1,2...master参照
	int event_type_ = 0;
	//変化するステータス
	int status_type_ = 0;
	//変化量
	int num_ = 0;
	//説明
	std::string desc_ = {};
	//変化するステータスの名前
	std::string StatusName_;

	//******カード用ステータス*****//
	//２つ目の変化するステータス
	int event_type_second_ = 0;
	int status_type_second_ = 0;
	int num_second_ = 0;
#endif
	//eventID
	int Id = 0;
	//0,1,2...master参照
	int Event_type = 0;

	int Atk_Num = 0;
	int Def_Num = 0;
	int MAtk_Num = 0;
	int MDef_Num = 0;
	int Spd_Num = 0;
	int Mind_Num = 0;
	int Vit_Num = 0;

	//説明
	std::string Desc = {};

	//追加するアビリティのタイプ -1なら追加しない
	int AbilityType = -1;
	//追加するアビリティのid -1なら追加しない
	int AbilityId = -1;

	//変化させるテンション -1→+2
	int Tension = 0;
	//追加するアイテムのid -1なら追加しない
	int Item_id = -1;


	////変化するステータスの名前
	//std::string StatusName_second_;

	//変化するステータスの名前
	std::vector<std::string> changeStatusName = {};
	//変化するステータスの量
	std::vector<int> changeStatusValue = {};

	void run_Card_Event(int passedDay);

	void AddNameToVector();

};