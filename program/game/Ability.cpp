#include "Ability.h"

Ability::Ability(int id, int abilitytype, std::string name, int atk, int def, int matk, int mdef, int spd, int min, int vit,
	std::string abilitydesc, std::string desc, int rank)
{
	int id_ = id;
	int ability_type_ = abilitytype;
	std::string ability_name = name;


	int atk_ = atk;
	int def_ = def;
	int matk_ = matk;
	int mdef_ = mdef;
	int spd_ = spd;
	int min_ = min;
	int vit_ = vit;

	std::string ability_desc_ = abilitydesc;
	std::string desc_ =desc;

	int rank_ = rank;

}

Ability::~Ability()
{
}
