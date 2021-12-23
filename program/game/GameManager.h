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
	//��x�ǂݍ���gh��ۑ�����map
	std::unordered_map<std::string, int> ghmap;

	//[itemid][haveItemNum]�A�C�e���������Ă��鐔��id�̓񎟌��z��
	std::vector<std::vector<int>> haveItem;
	//item���ׂĂ̔z��
	std::vector<std::vector<Item*>> itemList;

	/*int[] haveItem = {};*/

	int statusAlfa_SS_gh = 0;
	int statusAlfa_S_gh = 0;
	int statusAlfa_A_gh = 0;
	int statusAlfa_B_gh = 0;
	int statusAlfa_C_gh = 0;
	int statusAlfa_D_gh = 0;
	int statusAlfa_E_gh = 0;
	int statusAlfa_F_gh = 0;
	int statusAlfa_G_gh = 0;

	//�X�e�[�^�X�摜�̃��[�h
	void LoadStatusImage();

	float deitatime_;

	bool isInput = false;
	int InputHandle = 0;

	//�L�����𐶐�����֐�
	void MakeCharacter(const std::string& name, int year);

	//�L�������ݐ�vector����O���֐�
	void ExitCharaVec();

	//���O����͂���֐�
	void InputName(std::string name);

	//�X�e�[�^�X�ω��֐�
	//setType���ǂ̃X�e�[�^�X��ω������邩
	//value���ω���
	void StatusSet(int setType, int value);
	//�J�[�h�p�̃X�e�[�^�X�ω��֐�
	void StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit, int passedDay);
	//�A�r���e�B�̕t�^�֐�
	void AbilitySet(int abilityType, int abilityId);
	//�g���[�j���O��I������֐�
	void TrainingSet(Chara* setChara, int id);



	void Update();
	void Draw();
	//GameManager�̏�����
	void initGameManager();
	//�摜��ǂݍ����map�ɓ����֐�
	//���łɂ���gh�Ȃ炻���Ԃ�
	int LoadGraphEx(std::string gh);
	//�Z�[�u�ɕK�v�ȃV�[�����̃f�[�^���擾����֐�
	void GetSceneData();

	//gh��Ԃ��֐�
	std::vector<int> SetCharaGh(int num);

	std::string GetAbility(int abilityType, int abilityId);
	//�A�C�e���̏��������������߂�֐�
	void haveItemInit();

	void setitem(int ItemId, int addNum);

	//�w�N����グ��֐�
	void stayYearUp();

private:
	//char String[256] = {};


	//�L�����N�^�[�摜��excel����ǂݎ��֐�
	void loadCharaCsv();
	//�A�C�e������excel����ǂݎ��֐�
	void loadItem();

	std::vector<std::vector<std::string>> loadGhCsv;
	std::vector<std::vector<int>> charaGh;

	std::vector<std::vector<std::string>> loadItemCsv;


	//�X�e�[�^�X��1�オ�邽�߂ɕK�v�Ȍo���l�e�[�u��
	int needExp[11] = { 20,40,80,160,320,480,600,720,840,960,1080 };

	//���̃X�e�[�^�X�̒l������ƕK�v�o���l�e�[�u���̔z��ԍ����擾����֐�
	int GetDecNum(int nowStatus);



	//�o���l��^����֐�
	//c���^����L����,num���X�e�[�^�X�ԍ�
	void GiveExperience(Chara* c, int num, int PassedDay);




};