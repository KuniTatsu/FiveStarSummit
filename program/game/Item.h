#pragma once
#include<string>

class Ability;
class Menu;

class Item {

public:

	Item(int Id, int ItemType, int SetDay, int AddStatusType, int AddStatusNum,int SetAbilityId,int SetAbilityType, 
			std::string Gh, std::string Desc, std::string Name,int Num);
	~Item();

	
	Menu* frame = nullptr;
	Menu* button = nullptr;
	//itemId
	int id = 0;
	//ItemType
	int itemType = 0;
	//���ɂ��w��n�A�C�e���̓��ɂ�
	int setDay = 0;

	//�X�e�[�^�X�㏸�n�A�C�e����type
	int addStatusType = 0;
	//�X�e�[�^�X�㏸�n�A�C�e���̏㏸��
	int addStatusNum = 0;

	//ability�t�^�A�C�e���̃A�r���e�BID
	int setAbilityId = 0;
	//ability�t�^�A�C�e����type
	int setAbilityType = 0;

	//�摜�n���h����URL
	std::string gh_pass = "";

	//����
	std::string desc = "";

	//���O
	std::string name = "";

	//�ʂ��ԍ�
	int num = 0;

	//gh
	int gh = 0;

private:

	
};