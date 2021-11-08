#pragma once
#include<list>
#include<vector>
#include<string>


class Ability;

class AbilityManager {
	
public:
	AbilityManager();
	~AbilityManager();

	
	//csvから受け取ってくる二次元配列
	std::vector< std::vector<std::string> > ability_all;
	//typeごとに分けられたアビリティの2次元配列
	std::vector<std::vector<Ability*> >abilityList;

private:
	void LoadAbility();

};