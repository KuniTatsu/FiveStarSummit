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
#include"Item.h"
#include "FadeControl.h"
#include "SoundManager.h"



GameManager::GameManager()
{

}

GameManager::~GameManager()
{

	delete aManager;
	delete fControl;
	delete sound;

}

void GameManager::LoadStatusImage()
{
	statusAlfa_SS_gh = LoadGraphEx("graphics/Status_alfa_SS.png");
	statusAlfa_S_gh = LoadGraphEx("graphics/Status_alfa_S.png");
	statusAlfa_A_gh = LoadGraphEx("graphics/Status_alfa_A.png");
	statusAlfa_B_gh = LoadGraphEx("graphics/Status_alfa_B.png");
	statusAlfa_C_gh = LoadGraphEx("graphics/Status_alfa_C.png");
	statusAlfa_D_gh = LoadGraphEx("graphics/Status_alfa_D.png");
	statusAlfa_E_gh = LoadGraphEx("graphics/Status_alfa_E.png");
	statusAlfa_F_gh = LoadGraphEx("graphics/Status_alfa_F.png");
	statusAlfa_G_gh = LoadGraphEx("graphics/Status_alfa_G.png");
}

void GameManager::MakeCharacter(const std::string& name, int year)
{
	chara_ = new Chara(name, year);

	int random = GetRand(charaGh.size() - 1);
	//chara_->gh


	chara_->gh = SetCharaGh(random);

	chara.emplace_back(chara_);
	//InputName(name);
}

void GameManager::ExitCharaVec()
{
	auto it = chara.begin();
	while (it != chara.end()) {
		if ((*it)->charadata->stayYear == 3) {
			//卒業生vectorに格納
			exitChara.emplace_back((*it));
			it = chara.erase(it);
			continue;
		}
		it++;
	}
}
//キャラクターの名前を入力する関数(未実装)
void GameManager::InputName(std::string name)
{
	isInput = true;
	if (InputHandle != 0)return;
	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	//DrawStringEx(800, 600, -1, "入力中だよ");

	//入力を始めたいところで
	SetActiveKeyInput(InputHandle);

	//以降の入力はすべてInputHandleに行く

	//毎フレーム実行が必要なのでUpdateに移動


}

//DayCellによって与えられるステータス経験値
void GameManager::StatusSet(int setType, int value)
{

	if (0 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_ATACK += value;
			if (c->charadata->EXP_ATACK <= 0)c->charadata->EXP_ATACK = 0;
			if (c->charadata->EXP_ATACK >= needExp[GetDecNum(c->charadata->ATACK)]) {
				c->charadata->EXP_ATACK = 0;
				//すでに上限なら上昇させない
				if (c->charadata->ATACK == 100)return;
				c->charadata->ATACK += 1;
			}
		}
	}
	//DEFENCE
	else if (1 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_DEFENCE += value;
			if (c->charadata->EXP_DEFENCE <= 0)c->charadata->EXP_DEFENCE = 0;
			if (c->charadata->EXP_DEFENCE >= needExp[GetDecNum(c->charadata->DEFENCE)]) {
				c->charadata->EXP_DEFENCE = 0;
				//すでに上限なら上昇させない
				if (c->charadata->DEFENCE == 100)return;
				c->charadata->DEFENCE += 1;
			}
		}
	}
	//MAGIATACK
	else if (2 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_MAGIATACK += value;
			if (c->charadata->EXP_MAGIATACK <= 0)c->charadata->EXP_MAGIATACK = 0;
			if (c->charadata->EXP_MAGIATACK >= needExp[GetDecNum(c->charadata->MAGIATACK)]) {
				c->charadata->EXP_MAGIATACK = 0;
				//すでに上限なら上昇させない
				if (c->charadata->MAGIATACK == 100)return;
				c->charadata->MAGIATACK += 1;
			}
		}
	}
	//MAGIDEFENCE
	else if (3 == setType) {
		for (auto c : chara) {

			c->charadata->MAGIDEFENCE += value;
			if (c->charadata->EXP_MAGIDEFENCE <= 0)c->charadata->EXP_MAGIDEFENCE = 0;
			if (c->charadata->EXP_MAGIDEFENCE >= needExp[GetDecNum(c->charadata->MAGIDEFENCE)]) {
				c->charadata->EXP_MAGIDEFENCE = 0;
				//すでに上限なら上昇させない
				if (c->charadata->MAGIDEFENCE == 100)return;
				c->charadata->MAGIDEFENCE += 1;
			}
		}
	}
	//SPEED
	else if (4 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_SPEED += value;
			if (c->charadata->EXP_SPEED <= 0)c->charadata->EXP_SPEED = 0;
			if (c->charadata->EXP_SPEED >= needExp[GetDecNum(c->charadata->SPEED)]) {
				c->charadata->EXP_SPEED = 0;
				//すでに上限なら上昇させない
				if (c->charadata->SPEED == 100)return;
				c->charadata->SPEED += 1;
			}
		}
	}
	//MIND
	else if (5 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_MIND += value;
			if (c->charadata->EXP_MIND <= 0)c->charadata->EXP_MIND = 0;
			if (c->charadata->EXP_MIND >= needExp[GetDecNum(c->charadata->MIND)]) {
				c->charadata->EXP_MIND = 0;
				//すでに上限なら上昇させない
				if (c->charadata->MIND == 100)return;
				c->charadata->MIND += 1;
			}
		}
	}
	//VITALITY
	else if (6 == setType) {
		for (auto c : chara) {

			c->charadata->EXP_VITALITY += value;
			if (c->charadata->EXP_VITALITY <= 0)c->charadata->EXP_VITALITY = 0;
			if (c->charadata->EXP_VITALITY >= needExp[GetDecNum(c->charadata->VITALITY)]) {
				c->charadata->EXP_VITALITY = 0;
				//すでに上限なら上昇させない
				if (c->charadata->VITALITY == 100)return;
				c->charadata->VITALITY += 1;
			}

		}
	}
	

}

//カードによって与えられるステータス経験値
void GameManager::StatusSet(int atk, int def, int magiatk, int magidef, int spd, int mind, int vit, int passedDay)
{

	for (auto c : chara) {
		//カードのイベントの持つ経験値×経過日数の付与部分
		c->charadata->EXP_ATACK += atk * passedDay;
		c->charadata->EXP_DEFENCE += def * passedDay;
		c->charadata->EXP_MAGIATACK += magiatk * passedDay;
		c->charadata->EXP_MAGIDEFENCE += magidef * passedDay;
		c->charadata->EXP_SPEED += spd * passedDay;
		c->charadata->EXP_MIND += mind * passedDay;
		c->charadata->EXP_VITALITY += vit * passedDay;

		//キャラクター個人の強化項目の経験値付与
		for (int i = 0; i < 7; ++i) {
			//もしキャラクターの強化指定がおまかせだったら
			if (c->charadata->myTraining == Chara::trainingAll[0]) {
				int random = GetRand(7);

				//将来的にはキャラクターの全部のステータスが同じ値になるようにお任せを作りたい
				GiveExperience(c, random, passedDay);
				break;
			}
			//もしキャラクターの強化指定が〇〇だったら
			if (c->charadata->myTraining == Chara::trainingAll[i]) {
				GiveExperience(c, i, passedDay);
				break;
			}
		}
		//******閾値を突破していたときのステータス上昇処理******//
		if (c->charadata->EXP_ATACK >= needExp[GetDecNum(c->charadata->ATACK)]) {
			c->charadata->EXP_ATACK = 0;
			//すでに上限なら上昇させない
			if (c->charadata->ATACK == 100)return;
			c->charadata->ATACK += 1;
		}

		if (c->charadata->EXP_DEFENCE >= needExp[GetDecNum(c->charadata->DEFENCE)]) {
			c->charadata->EXP_DEFENCE = 0;
			//すでに上限なら上昇させない
			if (c->charadata->DEFENCE == 100)return;
			c->charadata->DEFENCE += 1;
		}

		if (c->charadata->EXP_MAGIATACK >= needExp[GetDecNum(c->charadata->MAGIATACK)]) {
			c->charadata->EXP_MAGIATACK = 0;
			//すでに上限なら上昇させない
			if (c->charadata->MAGIATACK == 100)return;
			c->charadata->MAGIATACK += 1;
		}

		if (c->charadata->EXP_MAGIDEFENCE >= needExp[GetDecNum(c->charadata->MAGIDEFENCE)]) {
			c->charadata->EXP_MAGIDEFENCE = 0;
			//すでに上限なら上昇させない
			if (c->charadata->MAGIDEFENCE == 100)return;
			c->charadata->MAGIDEFENCE += 1;
		}

		if (c->charadata->EXP_SPEED >= needExp[GetDecNum(c->charadata->SPEED)]) {
			c->charadata->EXP_SPEED = 0;
			//すでに上限なら上昇させない
			if (c->charadata->SPEED == 100)return;
			c->charadata->SPEED += 1;
		}

		if (c->charadata->EXP_MIND >= needExp[GetDecNum(c->charadata->MIND)]) {
			c->charadata->EXP_MIND = 0;
			//すでに上限なら上昇させない
			if (c->charadata->MIND == 100)return;
			c->charadata->MIND += 1;

		}

		if (c->charadata->EXP_VITALITY >= needExp[GetDecNum(c->charadata->VITALITY)]) {
			c->charadata->EXP_VITALITY = 0;
			//すでに上限なら上昇させない
			if (c->charadata->VITALITY == 100)return;
			c->charadata->VITALITY += 1;
		}
		//******************//



	}

}

void GameManager::AbilitySet(int abilityType, int abilityId)
{

	int count = 0;
	for (auto c : chara) {
		//1/10の確率でアビリティを付与する
		int random = GetRand(10);

		//***debug***//
		//int random = 9;
		//***********//

		if (random > 8) {

			//*******なんか複数個同じアビリティが登録されてるバグある*******//
			bool checkAlreadyhave = false;
			int i = 0;
			//ここのfor分がうまく回ってない
			//すでに持っているアビリティだったら追加せずに飛ばす
			for (auto abi : c->charadata->Ability) {

				if (abi->ability_name == aManager->abilityList[abilityType][abilityId]->ability_name) {
					checkAlreadyhave = true;
					break;
				}
				//i++;
			}
			if (checkAlreadyhave) {
				checkAlreadyhave = false;
				continue;
			}
			c->charadata->Ability.emplace_back(aManager->abilityList[abilityType][abilityId]);
			c->recentAddedAbility = aManager->abilityList[abilityType][abilityId]->ability_name;
			count += 1;

		}

	}
}
void GameManager::TrainingSet(Chara* setChara, int id)
{
	setChara->charadata->myTraining = Chara::trainingAll[id];
}
void GameManager::Update()
{
	SceneManager::Update();
	/*名前入力処理(未実装)
	//文字入力が終了しているならwhileループを抜ける
	if (InputHandle != 0 && CheckKeyInput(InputHandle) != 0) {

		//入力された文字列の取得
		GetKeyInputString(String, InputHandle);

		DeleteKeyInput(InputHandle);
		InputHandle = 0;
		//string型に変換
		std::string name(String, sizeof(String) / sizeof(String[0]));
		isInput = false;

		******debug*****
		//std::string name = "test";


		chara_ = new Chara(name, 1);
		chara.emplace_back(chara_);


	}
	else {
		//入力モードの描画
		DrawKeyInputModeString(640, 480);


		t2k::debugTrace("\n入力中\n");

		//DrawBox(50, 50, 100, 100, -1, true);
		//入力途中の文字列の描画
		DrawKeyInputString(200, 200, InputHandle);
	}
	*/
}

void GameManager::Draw()
{
	SceneManager::Render();
}

void GameManager::initGameManager()
{
	aManager = new AbilityManager();
	//dManager = new DataManager();
	sound = new Sound();
	fControl = new FadeControl();

	deitatime_ = 0;
	loadCharaCsv();
	SceneManager::ChangeScene(SceneManager::SCENE::TITLE);

	itemList.resize(3);
	loadItem();

	haveItem.resize(38);

	haveItemInit();
	LoadStatusImage();
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
//未実装
void GameManager::GetSceneData()
{


}

std::vector<int> GameManager::SetCharaGh(int num)
{
	return charaGh[num];
}

std::string GameManager::GetAbility(int abilityType, int abilityId)
{
	std::string ability = aManager->abilityList[abilityType][abilityId]->ability_name;

	return ability;
}

void GameManager::haveItemInit()
{
	for (int i = 0; i < haveItem.size(); ++i) {
		//アイテムi番を〇〇個で初期化する
		haveItem[i].emplace_back(1);
	}
}

void GameManager::setitem(int ItemId, int addNum)
{
	haveItem[ItemId][0] += addNum;
}

void GameManager::loadCharaCsv()
{
	loadGhCsv = t2k::loadCsv("Csv/CharaPass.csv");
	for (int i = 1; i < loadGhCsv.size() - 1; ++i) {

		int hoge[3] = {};
		std::string Pass = loadGhCsv[i][1];
		LoadDivGraph(Pass.c_str(), 3, 3, 1, 32, 32, hoge, false);


		std::vector<int> gh;
		charaGh.emplace_back(gh);
		charaGh[i - 1].emplace_back(hoge[0]);
		charaGh[i - 1].emplace_back(hoge[1]);
		charaGh[i - 1].emplace_back(hoge[2]);
	}
}

void GameManager::loadItem()
{
	loadItemCsv = t2k::loadCsv("Csv/Item.csv");
	for (int i = 1; i < loadItemCsv.size(); ++i) {

		//id
		int a = std::atoi(loadItemCsv[i][0].c_str());
		//ItemType
		int b = std::atoi(loadItemCsv[i][1].c_str());
		//setDay
		int c = std::atoi(loadItemCsv[i][2].c_str());
		//addStatus
		int d = std::atoi(loadItemCsv[i][3].c_str());
		//addStatusNum
		int e = std::atoi(loadItemCsv[i][4].c_str());
		//setAbility
		int f = std::atoi(loadItemCsv[i][5].c_str());
		//setAbilityType
		int g = std::atoi(loadItemCsv[i][6].c_str());
		//num
		int h = std::atoi(loadItemCsv[i][10].c_str());


		Item* abi = new Item(a, b, c, d, e, f, g, loadItemCsv[i][7], loadItemCsv[i][8], loadItemCsv[i][9], h);

		//abilitytypeごとにリストに格納
		itemList[b].emplace_back(abi);
	}
}

int GameManager::GetDecNum(int nowStatus)
{
	if (nowStatus >= 90 && nowStatus < 96) {

		return 10;
	}
	else if (nowStatus >= 96) {
		return 9;
	}
	int DecNum = nowStatus / 10;

	return DecNum;
}

void GameManager::stayYearUp()
{
	auto it = chara.begin();
	while (it != chara.end()) {
		(*it)->charadata->stayYear++;
		it++;
	}
}

void GameManager::GiveExperience(Chara* c, int num, int PassedDay)
{
	if (num == 0) {
		c->charadata->EXP_ATACK += 10 * PassedDay;
	}
	else if (num == 1) {
		c->charadata->EXP_DEFENCE += 10 * PassedDay;
	}
	else if (num == 2) {
		c->charadata->EXP_MAGIATACK += 10 * PassedDay;
	}
	else if (num == 3) {
		c->charadata->EXP_MAGIDEFENCE += 10 * PassedDay;
	}
	else if (num == 4) {
		c->charadata->EXP_SPEED += 10 * PassedDay;
	}
	else if (num == 5) {
		c->charadata->EXP_MIND += 10 * PassedDay;
	}
	else if (num == 6) {
		c->charadata->EXP_VITALITY += 10 * PassedDay;
	}


}

