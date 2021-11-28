#include "GameManager.h"
#include"SceneManager.h"
#include"Character.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"
#include<string>
#include"AbilityManager.h"
#include"Ability.h"
#include"DataManager.h"



GameManager::GameManager()
{
	//aManager = new AbilityManager();
	////dManager = new DataManager();
	////sManager = new SceneManager();
	//deitatime_ = 0;

	//SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);
}

GameManager::~GameManager()
{
}

void GameManager::MakeCharacter()
{

	InputName();

	////string型に変換
	//std::string name(String, sizeof(String) / sizeof(String[0]));
	//isInput = false;

	//////******debug*****
	////std::string name = "test";


	//chara_ = new Chara(name);
	//chara.emplace_back(chara_);


}

void GameManager::InputName()
{
	isInput = true;
	if (InputHandle != 0)return;
	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	//DrawStringEx(800, 600, -1, "入力中だよ");

	//入力を始めたいところで
	SetActiveKeyInput(InputHandle);

	//以降の入力はすべてInputHandleに行く

	//毎フレーム実行が必要なのでUpdateに移動
#if 0

	while (!ProcessMessage()) {


		//文字入力が終了しているならwhileループを抜ける
		//if (CheckKeyInput(InputHandle) != 0)break;

		//入力モードの描画↓出ない
		DrawKeyInputModeString(640, 480);
		//↓出ない
		DrawBox(200, 200, 640, 480, -1, true);

		//↓出る
		//t2k::debugTrace("\n入力中\n");

		//入力途中の文字列の描画↓出ない
		DrawKeyInputString(0, 0, InputHandle);

	}

	//入力された文字列の取得
	GetKeyInputString(String, InputHandle);

	DeleteKeyInput(InputHandle);
#endif


}

//スキル付与イベントは負の値だった場合無視するコードを冒頭に入れる

void GameManager::StatusSet(int setType, int value)
{
	//もしATACK上昇させたいなら
	//0:ATACK,...

	//int MAGIATACK;	//魔法攻撃力
	//int MAGIDEFENCE;//魔法防御力
	//int SPEED;		//素早さ
	//int MIND;		//賢さ
	//int VITALITY;	//持久力
	if (0 == setType) {
		for (auto c : chara) {

			c->charadata->ATACK += value;
			if (c->charadata->ATACK <= 0)c->charadata->ATACK = 0;
		}
	}
	//DEFENCE
	else if (1 == setType) {
		for (auto c : chara) {

			c->charadata->DEFENCE += value;
			if (c->charadata->DEFENCE <= 0)c->charadata->DEFENCE = 0;
		}
	}
	//MAGIATACK
	else if (2 == setType) {
		for (auto c : chara) {

			c->charadata->MAGIATACK += value;
			if (c->charadata->MAGIATACK <= 0)c->charadata->MAGIATACK = 0;
		}
	}
	//MAGIDEFENCE
	else if (3 == setType) {
		for (auto c : chara) {

			c->charadata->MAGIDEFENCE += value;
			if (c->charadata->MAGIDEFENCE <= 0)c->charadata->MAGIDEFENCE = 0;
		}
	}
	//SPEED
	else if (4 == setType) {
		for (auto c : chara) {

			c->charadata->SPEED += value;
			if (c->charadata->SPEED <= 0)c->charadata->SPEED = 0;
		}
	}
	//MIND
	else if (5 == setType) {
		for (auto c : chara) {

			c->charadata->MIND += value;
			if (c->charadata->MIND <= 0)c->charadata->MIND = 0;
		}
	}
	//VITALITY
	else if (6 == setType) {
		for (auto c : chara) {

			c->charadata->VITALITY += value;
			if (c->charadata->VITALITY <= 0)c->charadata->VITALITY = 0;

		}
	}
	//else if

}

void GameManager::StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit)
{

	for (auto c : chara) {

		c->charadata->ATACK += atk;
		c->charadata->DEFENCE += def;
		c->charadata->MAGIATACK += magiatk;
		c->charadata->MAGIDEFENCE += magidef;
		c->charadata->SPEED += spd;
		c->charadata->MIND += mind;
		c->charadata->VITALITY += vit;

		if (c->charadata->ATACK <= 0)c->charadata->ATACK = 0;
		if (c->charadata->DEFENCE <= 0)c->charadata->DEFENCE = 0;
		if (c->charadata->MAGIATACK <= 0)c->charadata->MAGIATACK = 0;
		if (c->charadata->MAGIDEFENCE <= 0)c->charadata->MAGIDEFENCE = 0;
		if (c->charadata->SPEED <= 0)c->charadata->SPEED = 0;
		if (c->charadata->MIND <= 0)c->charadata->MIND = 0;
		if (c->charadata->VITALITY <= 0)c->charadata->VITALITY = 0;
	}

}

void GameManager::AbilitySet(int abilityType, int abilityId)
{
	//最後のキャラの時点でcountが0ならそのキャラにアビリティを付与する？？
	int count = 0;
	for (auto c : chara) {
		//1/10の確率でアビリティを付与する
		int random = GetRand(10);
		if (random > 8) {

			//なんか複数個同じアビリティが登録されてるバグある
			bool checkAlreadyhave = false;
			int i = 0;
			//すでに持っているアビリティだったら追加せずに飛ばす
			for (auto abi : c->charadata->Ability) {

				if (abi[i].ability_name == aManager->abilityList[abilityType][abilityId]->ability_name)checkAlreadyhave = true;
				i++;
			}
			if (checkAlreadyhave)return;
			c->charadata->Ability.emplace_back(aManager->abilityList[abilityType][abilityId]);
			c->recentAddedAbility = aManager->abilityList[abilityType][abilityId]->ability_name;
			count += 1;
		}

	}
}
void GameManager::Update()
{
	SceneManager::Update();

	//文字入力が終了しているならwhileループを抜ける
	if (InputHandle != 0 && CheckKeyInput(InputHandle) != 0) {

		//入力された文字列の取得
		GetKeyInputString(String, InputHandle);

		DeleteKeyInput(InputHandle);
		InputHandle = 0;
		//string型に変換
		std::string name(String, sizeof(String) / sizeof(String[0]));
		isInput = false;

		////******debug*****
		//std::string name = "test";


		chara_ = new Chara(name);
		chara.emplace_back(chara_);


	}
	else {


		//入力モードの描画↓出ない
		DrawKeyInputModeString(640, 480);

		//↓出る
		//t2k::debugTrace("\n入力中\n");

		//入力途中の文字列の描画↓出ない
		DrawKeyInputString(0, 0, InputHandle);
	}

}

void GameManager::Draw()
{
	if (isInput == false) {
		DrawStringEx(800, 500, -1, "false");
	}
	else {
		DrawStringEx(800, 500, -1, "true");
	}
	SceneManager::Render();
	/*if (chara.empty())return;
	CharactorStatusDraw();*/

	//debug
	/*std::string hoge = aManager->abilityList[0][0]->ability_name;
	DrawStringEx(800, 700, -1, "%s", hoge);*/

}

void GameManager::initGameManager()
{
	aManager = new AbilityManager();
	//dManager = new DataManager();
	//sManager = new SceneManager();
	deitatime_ = 0;

	SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);


}

int GameManager::LoadGraphEx(std::string gh)
{

	auto it = ghmap.find(gh);
	if (it != ghmap.end()) {
		return ghmap[gh];
	}

	else {
		int loadgh = LoadGraph(gh.c_str());
		ghmap.insert(std::make_pair(gh, loadgh));
	}


	return ghmap[gh];
}

std::string GameManager::GetAbility(int abilityType, int abilityId)
{
	std::string ability = aManager->abilityList[abilityType][abilityId]->ability_name;

	return ability;
}
