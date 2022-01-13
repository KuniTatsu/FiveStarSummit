#pragma once
#include<vector>
#include<string>
class Skill;
class Chara;

class SkillManager
{
public:
	SkillManager();
	~SkillManager();

	std::vector < std::vector<std::string>>loadedSkill;

	//ƒXƒLƒ‹‚ª‘S‚Ä“ü‚Á‚½vector Œ•,‘„,ñ,‹|,Œ‚Ì‡‚É0¨4
	std::vector<std::vector<Skill*>> skillAll;

	void SetSkill(Chara* c);

private:

	void LoadSkill();


};

