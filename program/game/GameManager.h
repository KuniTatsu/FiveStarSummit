#pragma once
#include<vector>
#include<string>
#include<unordered_map>
class SceneManager;
class Chara;
class AbilityManager;
class DataManager;

class GameManager {

public:

	GameManager();
	~GameManager();

	SceneManager* sManager = nullptr;
	Chara* chara_ = nullptr;
	AbilityManager* aManager = nullptr;
	DataManager* dManager = nullptr;

	std::vector<Chara*> chara = {};

	std::unordered_map<std::string, int> ghmap;

	float deitatime_;

	bool isInput = false;
	int InputHandle=0;

	//�L�����𐶐�����֐�
	void MakeCharacter(const std::string& name,int year);

	//���O����͂���֐�
	void InputName(std::string name);

	//�X�e�[�^�X�ω��֐�
	//setType���ǂ̃X�e�[�^�X��ω������邩
	//value���ω���
	void StatusSet(int setType, int value);

	void StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit);

	void AbilitySet(int abilityType, int abilityId);





	//debug�p�Ɉ�U�����ō��
	//void CharactorStatusDraw();

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
	void loadCharaCsv();

	std::vector<std::vector<std::string>> loadGhCsv;
	std::vector<std::vector<int>> charaGh;

	int needExp[11] = { 20,40,80,160,320,480,600,720,840,960,1080 };

	//���̃X�e�[�^�X�̒l������ƕK�v�o���l�e�[�u���̔z��ԍ����擾����֐�
	int GetDecNum(int nowStatus);
	

};