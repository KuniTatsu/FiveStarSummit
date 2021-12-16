#pragma once
#include<vector>
#include<string>
#include<unordered_map>
class SceneManager;
class Chara;
class AbilityManager;
class DataManager;
class Item;

class GameManager {

public:

	GameManager();
	~GameManager();

	SceneManager* sManager = nullptr;
	Chara* chara_ = nullptr;
	AbilityManager* aManager = nullptr;
	DataManager* dManager = nullptr;

	//�ݐЂ���L�����N�^�[
	std::list<Chara*> chara = {};

	//���Ƃ����L�����N�^�[
	std::vector<Chara*> exitChara = {};

	std::unordered_map<std::string, int> ghmap;

	float deitatime_;

	bool isInput = false;
	int InputHandle=0;

	//�L�����𐶐�����֐�
	void MakeCharacter(const std::string& name,int year);

	//�L�������ݐ�vector����O���֐�
	void ExitCharaVec();

	//���O����͂���֐�
	void InputName(std::string name);

	//�X�e�[�^�X�ω��֐�
	//setType���ǂ̃X�e�[�^�X��ω������邩
	//value���ω���
	void StatusSet(int setType, int value);

	void StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit, int passedDay);

	void AbilitySet(int abilityType, int abilityId);

	void TrainingSet(Chara* setChara,int id);

	

	void Update();
	void Draw();
	void initGameManager();
	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string gh);

	//gh��Ԃ��֐�
	std::vector<int> SetCharaGh(int num);

	std::string GetAbility(int abilityType, int abilityId);

private:
	char String[256] = {};
	//�L�����N�^�[�摜��excel����ǂݎ��֐�
	void loadCharaCsv();
	//�A�C�e������excel����ǂݎ��֐�
	void loadItem();

	std::vector<std::vector<std::string>> loadGhCsv;
	std::vector<std::vector<int>> charaGh;

	std::vector<std::vector<std::string>> loadItemCsv;
	std::vector<std::vector<Item*>> itemList;

	//�X�e�[�^�X��1�オ�邽�߂ɕK�v�Ȍo���l�e�[�u��
	int needExp[11] = { 20,40,80,160,320,480,600,720,840,960,1080 };

	//���̃X�e�[�^�X�̒l������ƕK�v�o���l�e�[�u���̔z��ԍ����擾����֐�
	int GetDecNum(int nowStatus);
	
	//�o���l��^����֐�
	//c���^����L����,num���X�e�[�^�X�ԍ�
	void GiveExperience(Chara* c,int num,int PassedDay);

};