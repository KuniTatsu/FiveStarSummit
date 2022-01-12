#include "Skill.h"

Skill::Skill(int Id, int Type, std::string Name, int Status, int Increase, float ChargeTime, float ReCastTime, 
			int Range_Width, int Range_Height, bool Penetrate, bool KnockBack, int Stan, std::string SDesc, std::string Desc)
{
	id = Id;
	skilltype = Type;
	SkillName = Name;
	increaseNum = Increase;
	chargeTime = ChargeTime;
	reCastTime = ReCastTime;
	rangeWidth = Range_Width;
	rangeHeight = Range_Height;
	canPenetrate = Penetrate;
	canKnockBack = KnockBack;
	stan = Stan;
	skillDesc = SDesc;
	desc = Desc;

}
