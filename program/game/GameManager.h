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

	//名前を入力する関数
	void InputName();

	//ステータス変化関数
	//setType→どのステータスを変化させるか
	//value→変化量
	void StatusSet(int setType, int value);

	//debug用に一旦ここで作る
	//void CharactorStatusDraw();

	void Update();
	void Draw();
	void initGameManager();
	int LoadGraphEx(std::string gh);

private:
	char String[256] = {};



};