#pragma once

class Ability;

class Item {

public:

	Item();
	~Item();


	//itemId
	int id = 0;
	//���ɂ��w��n�A�C�e���̓��ɂ�
	int setDay = 0;

	//�X�e�[�^�X�㏸�n�A�C�e���̏㏸��
	int addStatus = 0;
	//ability�t�^�A�C�e���̃A�r���e�B
	Ability* setAbility = nullptr;



private:


};