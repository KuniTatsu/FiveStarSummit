#pragma once
#include<list>
#include<vector>
#include<string>


class Ability;

class AbilityManager {
	
public:
	AbilityManager();
	~AbilityManager();

	
	//csv����󂯎���Ă���񎟌��z��
	std::vector< std::vector<std::string> > ability_all;
	//type���Ƃɕ�����ꂽ�A�r���e�B��2�����z��
	std::vector<std::vector<Ability*> >abilityList;

private:
	void LoadAbility();

};