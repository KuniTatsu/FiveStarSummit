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
	//setType→どのステータスを変化させるか
	//value→変化量
	void StatusSet(int setType, int value);

	//debug用に一旦ここで作る
	void CharactorStatusDraw();

	void Update();
	void Draw();


};