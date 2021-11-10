#include "Ability.h"

Ability::Ability(int id, int abilitytype, std::string name, int atk, int def, int matk, int mdef, int spd, int min, int vit,
	std::string abilitydesc, std::string desc, int rank)
{
	id_ = id;
	ability_type_ = abilitytype;
	ability_name = name;


	atk_ = atk;
	def_ = def;
	matk_ = matk;
	mdef_ = mdef;
	spd_ = spd;
	min_ = min;
	vit_ = vit;

	ability_desc_ = abilitydesc;
	desc_ = desc;

	rank_ = rank;

}

Ability::~Ability()
{
}
