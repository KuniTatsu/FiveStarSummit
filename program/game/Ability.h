#pragma once
#include<string>


class Ability {
public:

	Ability(int id, int abilitytype, std::string name, int atk, int def, int matk, int mdef, int spd, int min, int vit,
		std::string abilitydesc, std::string desc, int rank);
	~Ability();
	//�A�r���e�Bid
	int id_ = 0;
	//�A�r���e�B�^�C�v:0����ʔ\�͏㏸,1���펞�\�͏㏸,2�����Ҕ\�͏㏸
	int ability_type_ = 0;
	//�A�r���e�B�̖��O
	std::string ability_name = {};

	//******�X�e�[�^�X�ω���******/////

	int atk_ = 0;
	int def_ = 0;
	int matk_ = 0;
	int mdef_ = 0;
	int spd_ = 0;
	int min_ = 0;
	int vit_ = 0;
	//*****************************//
	//�A�r���e�B�̐���
	std::string ability_desc_ = {};
	//�A�r���e�B�̂��̑�����
	std::string desc_ = {};
	//�A�r���e�B�̃����N:0����ʃX�L��,1���㋉�X�L��
	int rank_ = 0;


};