#pragma once
#include<vector>
#include<string>
#include<unordered_map>
class SceneManager;
class Chara;
class AbilityManager;
class DataManager;
class Item;

class GameManager {

public:

	GameManager();
	~GameManager();

	SceneManager* sManager = nullptr;
	Chara* chara_ = nullptr;
	AbilityManager* aManager = nullptr;
	DataManager* dManager = nullptr;

	//在籍するキャラクター
	std::list<Chara*> chara = {};

	//卒業したキャラクター
	std::vector<Chara*> exitChara = {};

	std::unordered_map<std::string, int> ghmap;

	float deitatime_;

	bool isInput = false;
	int InputHandle=0;

	//キャラを生成する関数
	void MakeCharacter(const std::string& name,int year);

	//キャラを在籍vectorから外す関数
	void ExitCharaVec();

	//名前を入力する関数
	void InputName(std::string name);

	//ステータス変化関数
	//setType→どのステータスを変化させるか
	//value→変化量
	void StatusSet(int setType, int value);

	void StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit, int passedDay);

	void AbilitySet(int abilityType, int abilityId);

	void TrainingSet(Chara* setChara,int id);

	

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
	//キャラクター画像をexcelから読み取る関数
	void loadCharaCsv();
	//アイテム情報をexcelから読み取る関数
	void loadItem();

	std::vector<std::vector<std::string>> loadGhCsv;
	std::vector<std::vector<int>> charaGh;

	std::vector<std::vector<std::string>> loadItemCsv;
	std::vector<std::vector<Item*>> itemList;

	//ステータスが1上がるために必要な経験値テーブル
	int needExp[11] = { 20,40,80,160,320,480,600,720,840,960,1080 };

	//今のステータスの値を入れると必要経験値テーブルの配列番号を取得する関数
	int GetDecNum(int nowStatus);
	
	//経験値を与える関数
	//c→与えるキャラ,num→ステータス番号
	void GiveExperience(Chara* c,int num,int PassedDay);

};