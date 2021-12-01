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
	void MakeCharacter(const std::string& name);

	//名前を入力する関数
	void InputName(std::string name);

	//ステータス変化関数
	//setType→どのステータスを変化させるか
	//value→変化量
	void StatusSet(int setType, int value);

	void StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit);

	void AbilitySet(int abilityType, int abilityId);





	//debug用に一旦ここで作る
	//void CharactorStatusDraw();

	void Update();
	void Draw();
	void initGameManager();
	int LoadGraphEx(std::string gh);

	std::string GetAbility(int abilityType, int abilityId);

private:
	char String[256] = {};



};