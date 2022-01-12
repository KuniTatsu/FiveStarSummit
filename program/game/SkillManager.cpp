#include "SkillManager.h"
#include"../library/t2klib.h"
#include"Skill.h"


SkillManager::SkillManager()
{
	//Œ•,‘„,ñ,‹|,Œ
	skillAll.resize(5);
	LoadSkill();
}

SkillManager::~SkillManager()
{
}

void SkillManager::SetSkill(Chara* c)
{
}
//14
//id(int)	Skill_Type(int)	Skill_Name(std::string)	EnhanceStatus(int)	IncreaseNum(int%)	ChargeTime(float)	ReCastTime(float)	Range_Width(int)	Range_Height(int)	Penetrate(bool)	KnockBack(bool)	Stan(int)	Skill_Desc	Desc
void SkillManager::LoadSkill()
{
	loadedSkill = t2k::loadCsv("Csv/Skill.csv");

	for (int i = 1; i < loadedSkill.size(); ++i) {

		//int int string int int float float int int bool bool int string string

		//excel‚©‚ç“Ç‚İæ‚Á‚½—ñ‚ğˆê‚Â‚¸‚Â•Ï”‚ÉŠi”[¨ƒCƒxƒ“ƒgƒNƒ‰ƒX‚ğ¶¬‚·‚é‚Æ‚«‚Ìˆø”‚É‚Ô‚¿‚Ş
		//id
		int a = std::atoi(loadedSkill[i][0].c_str());
		//skillType:0,1,2,3,4,5
		int b = std::atoi(loadedSkill[i][1].c_str());
		//EnhanceStatus
		int c = std::atoi(loadedSkill[i][3].c_str());
		//IncreaseNum
		int d = std::atoi(loadedSkill[i][4].c_str());
		//ChargeTime
		float e = std::stof(loadedSkill[i][5]);
		//ReCastTime
		float f = std::stof(loadedSkill[i][6]);
		//RangeWidth
		int g = std::atoi(loadedSkill[i][7].c_str());
		//RangeHeight
		int h = std::atoi(loadedSkill[i][8].c_str());
		//penetrate
		bool k = true;
		//knockback
		bool m = true;
		if (loadedSkill[i][9] == "FALSE") {
			k = false;
		}
		if (loadedSkill[i][10] == "FALSE") {
			m = false;
		}
		//stan
		int n = std::atoi(loadedSkill[i][11].c_str());

		//id,eventType,extraStatus_type,extraStatus_num,desc
		Skill* new_skill = new Skill(a,b, loadedSkill[i][2],c,d,e,f,g,h,k,m,n, loadedSkill[i][12], loadedSkill[i][13]);

		//skilltype‚²‚Æ‚ÉƒŠƒXƒg‚ÉŠi”[
		skillAll[b].emplace_back(new_skill);

	}



}
