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
	//一度読み込んだghを保存するmap
	std::unordered_map<std::string, int> ghmap;

	//[itemid][haveItemNum]アイテムを持っている数とidの二次元配列
	std::vector<std::vector<int>> haveItem;
	//itemすべての配列
	std::vector<std::vector<Item*>> itemList;

	/*int[] haveItem = {};*/

	int statusAlfa_SS_gh = 0;
	int statusAlfa_S_gh = 0;
	int statusAlfa_A_gh = 0;
	int statusAlfa_B_gh = 0;
	int statusAlfa_C_gh = 0;
	int statusAlfa_D_gh = 0;
	int statusAlfa_E_gh = 0;
	int statusAlfa_F_gh = 0;
	int statusAlfa_G_gh = 0;

	//ステータス画像のロード
	void LoadStatusImage();

	float deitatime_;

	bool isInput = false;
	int InputHandle = 0;

	//キャラを生成する関数
	void MakeCharacter(const std::string& name, int year);

	//キャラを在籍vectorから外す関数
	void ExitCharaVec();

	//名前を入力する関数
	void InputName(std::string name);

	//ステータス変化関数
	//setType→どのステータスを変化させるか
	//value→変化量
	void StatusSet(int setType, int value);
	//カード用のステータス変化関数
	void StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit, int passedDay);
	//アビリティの付与関数
	void AbilitySet(int abilityType, int abilityId);
	//トレーニングを選択する関数
	void TrainingSet(Chara* setChara, int id);



	void Update();
	void Draw();
	//GameManagerの初期化
	void initGameManager();
	//画像を読み込んでmapに入れる関数
	//すでにあるghならそれを返す
	int LoadGraphEx(std::string gh);
	//セーブに必要なシーン内のデータを取得する関数
	void GetSceneData();

	//ghを返す関数
	std::vector<int> SetCharaGh(int num);

	std::string GetAbility(int abilityType, int abilityId);
	//アイテムの初期所持数を決める関数
	void haveItemInit();

	void setitem(int ItemId, int addNum);

	//学年を一つ上げる関数
	void stayYearUp();

private:
	//char String[256] = {};


	//キャラクター画像をexcelから読み取る関数
	void loadCharaCsv();
	//アイテム情報をexcelから読み取る関数
	void loadItem();

	std::vector<std::vector<std::string>> loadGhCsv;
	std::vector<std::vector<int>> charaGh;

	std::vector<std::vector<std::string>> loadItemCsv;


	//ステータスが1上がるために必要な経験値テーブル
	int needExp[11] = { 20,40,80,160,320,480,600,720,840,960,1080 };

	//今のステータスの値を入れると必要経験値テーブルの配列番号を取得する関数
	int GetDecNum(int nowStatus);



	//経験値を与える関数
	//c→与えるキャラ,num→ステータス番号
	void GiveExperience(Chara* c, int num, int PassedDay);




};