#pragma once
#include<string>

class Skill {
public:
	//id(int)	Skill_Type(int)	Skill_Name(std::string)	EnhanceStatus(int)	IncreaseNum(int%)	ChargeTime(float)	ReCastTime(float)	Range_Width(int)	Range_Height(int)	Penetrate(bool)	KnockBack(bool)	Stan(int)	Skill_Desc	Desc

	Skill(int Id, int Type, std::string Name, int Status, int Increase, float ChargeTime, float ReCastTime, 
				int Range_Width, int Range_Height, bool Penetrate, bool KnockBack, int Stan, std::string SDesc, std::string Desc);

	int id = 0;
	int skilltype = 0;

	std::string SkillName = "";

	//強化されるステータス 0:atk,...
	int enhanceStatus = 0;
	//強化倍率(+n%)
	int increaseNum = 0;

	float chargeTime = 0;
	float reCastTime = 0;

	int rangeWidth = 0;
	int rangeHeight = 0;

	bool canPenetrate = true;
	bool canKnockBack = true;

	int stan = 0;

	std::string skillDesc = "";
	std::string desc = "";


};