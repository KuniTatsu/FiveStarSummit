#pragma once
#include<string>
#include<vector>

class CardEvent {

public:
	
	CardEvent(int id,int eventType,int atk, int def, int magiatk, int magidef, int spd, int mind, int vit, std::string desc, int abiType,int abiId,int tension,int itemid,std::string EventMessage,std::string TeachRef);
	~CardEvent();


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

	//イベントメッセージ
	std::string eventMessage="";

	//説明文
	std::string teachRef = "";

	void run_Card_Event(int passedDay);

	void AddNameToVector();

};