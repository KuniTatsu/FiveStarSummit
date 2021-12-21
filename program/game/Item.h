#pragma once
#include<string>

class Ability;
class Menu;

class Item {

public:

	Item(int Id, int ItemType, int SetDay, int AddStatusType, int AddStatusNum,int SetAbilityId,int SetAbilityType, 
			std::string Gh, std::string Desc, std::string Name,int Num);
	~Item();

	
	Menu* frame = nullptr;
	Menu* button = nullptr;
	//itemId
	int id = 0;
	//ItemType
	int itemType = 0;
	//日にち指定系アイテムの日にち
	int setDay = 0;

	//ステータス上昇系アイテムのtype
	int addStatusType = 0;
	//ステータス上昇系アイテムの上昇量
	int addStatusNum = 0;

	//ability付与アイテムのアビリティID
	int setAbilityId = 0;
	//ability付与アイテムのtype
	int setAbilityType = 0;

	//画像ハンドルのURL
	std::string gh_pass = "";

	//説明
	std::string desc = "";

	//名前
	std::string name = "";

	//通し番号
	int num = 0;

	//gh
	int gh = 0;

private:

	
};