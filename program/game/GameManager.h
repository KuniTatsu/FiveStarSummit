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

	//ステータス変化関数
	//setType→どのステータスを上げるか
	//valueEx→ステータス上昇係数 1→等倍(+10*1),2→倍(+10*2),3→3倍(+10*3)
	void StatusSet(int setType, int value);

	//debug用に一旦ここで作る
	void CharactorStatusDraw();

	void Update();
	void Draw();


};