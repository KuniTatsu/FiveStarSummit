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

	void MakeCharacter();

	//�X�e�[�^�X�ω��֐�
	//setType���ǂ̃X�e�[�^�X���グ�邩
	//valueEx���X�e�[�^�X�㏸�W�� 1�����{(+10*1),2���{(+10*2),3��3�{(+10*3)
	void StatusSet(int setType,int valueEx);

	void Update();
	void Draw();


};