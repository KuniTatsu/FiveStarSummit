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
	std::vector<std::vector<Skill*>> skillAll;

	void SetSkill(Chara* c);

private:

	void LoadSkill();


};

