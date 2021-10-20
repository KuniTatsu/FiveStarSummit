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

	//ステータス変化関数
	//setType→どのステータスを上げるか
	//valueEx→ステータス上昇係数 1→等倍(+10*1),2→倍(+10*2),3→3倍(+10*3)
	void StatusSet(int setType,int valueEx);

	void Update();
	void Draw();


};