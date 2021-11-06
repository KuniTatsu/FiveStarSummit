#include "AbilityManager.h"
#include"Ability.h"
#include<vector>
#include<string>
#include"DxLib.h"
#include"../library//t2klib.h"
#include"GameManager.h"
#include "DxLib.h"

extern GameManager* gManager;

AbilityManager::AbilityManager()
{


}

AbilityManager::~AbilityManager()
{


}

void AbilityManager::LoadAbility()
{

	ability_all = t2k::loadCsv("Csv/Ability.csv");
}
