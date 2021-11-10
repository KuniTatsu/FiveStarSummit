#pragma once
#include<vector>
#include<string>
class SceneManager;
class Chara;
class AbilityManager;

class GameManager {

public:

	GameManager();
	~GameManager();

	SceneManager* sManager = nullptr;
	Chara* chara_ = nullptr;
	AbilityManager* aManager = nullptr;

	std::vector<Chara*> chara = {};

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

private:
	char String[256] = {};



};