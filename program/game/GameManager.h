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
	void MakeCharacter();

	//���O����͂���֐�
	void InputName();

	//�X�e�[�^�X�ω��֐�
	//setType���ǂ̃X�e�[�^�X��ω������邩
	//value���ω���
	void StatusSet(int setType, int value);

	//debug�p�Ɉ�U�����ō��
	//void CharactorStatusDraw();

	void Update();
	void Draw();
	void initGameManager();
	int LoadGraphEx(std::string gh);

private:
	char String[256] = {};



};