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
	//画像を読み込んでmapに入れる関数
	//すでにあるghならそれを返す
	int LoadGraphEx(std::string gh);

	//ghを返す関数
	std::vector<int> SetCharaGh(int num);

	

	

	std::string GetAbility(int abilityType, int abilityId);

private:
	char String[256] = {};
	void loadCharaCsv();

	std::vector<std::vector<std::string>> loadGhCsv;
	std::vector<std::vector<int>> charaGh;

	int needExp[11] = { 20,40,80,160,320,480,600,720,840,960,1080 };

	//今のステータスの値を入れると必要経験値テーブルの配列番号を取得する関数
	int GetDecNum(int nowStatus);
	

};