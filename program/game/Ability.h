#pragma once
#include<string>


class Ability {
public:

	Ability(int id, int abilitytype, std::string name, int atk, int def, int matk, int mdef, int spd, int min, int vit,
		std::string abilitydesc, std::string desc, int rank);
	~Ability();

	//id(int)	AbilityType(int)	Ability_Name	ATACK	DEFENCE	MATACK	MDEFENCE	SPEED	MIND	VITALITY	Ability_Desc	Desc rank

	//アビリティid
	int id_ = 0;
	//アビリティタイプ:0→場面能力上昇,1→常時能力上昇,2→他者能力上昇
	int ability_type_ = 0;
	//アビリティの名前
	std::string ability_name = {};

	//******ステータス変化量******/////

	int atk_ = 0;
	int def_ = 0;
	int matk_ = 0;
	int mdef_ = 0;
	int spd_ = 0;
	int min_ = 0;
	int vit_ = 0;
	//*****************************//
	//アビリティの説明
	std::string ability_desc_ = {};
	//アビリティのその他説明
	std::string desc_ = {};
	//アビリティのランク:0→一般スキル,1→上級スキル
	int rank_ = 0;


};