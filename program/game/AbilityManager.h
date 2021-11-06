#pragma once
#include<list>
#include<vector>
#include<string>


class Ability;

class AbilityManager {
	
public:
	AbilityManager();
	~AbilityManager();

	

	std::vector< std::vector<std::string> > ability_all;
	std::vector<std::vector<Ability*> >abilityList;

private:
	void LoadAbility();

};