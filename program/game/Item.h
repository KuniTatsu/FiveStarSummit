#pragma once

class Ability;

class Item {

public:

	Item();
	~Item();


	//itemId
	int id = 0;
	//日にち指定系アイテムの日にち
	int setDay = 0;

	//ステータス上昇系アイテムの上昇量
	int addStatus = 0;
	//ability付与アイテムのアビリティ
	Ability* setAbility = nullptr;



private:


};