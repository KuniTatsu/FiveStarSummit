#pragma once
#include<vector>
class SceneManager;
class Chara;

class GameManager {

public:

	GameManager();
	~GameManager();

	SceneManager* sManager = nullptr;
	Chara* chara_ = nullptr;

	std::vector<Chara*> chara = {};

	float deitatime_;

	void MakeCharacter();

	//�X�e�[�^�X�ω��֐�
	//setType���ǂ̃X�e�[�^�X��ω������邩
	//value���ω���
	void StatusSet(int setType, int value);

	//debug�p�Ɉ�U�����ō��
	void CharactorStatusDraw();

	void Update();
	void Draw();


};