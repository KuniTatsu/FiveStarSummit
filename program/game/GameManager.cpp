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

	////stringŒ^‚É•ÏŠ·
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
	//DrawStringEx(800, 600, -1, "“ü—Í’†‚¾‚æ");

	//“ü—Í‚ðŽn‚ß‚½‚¢‚Æ‚±‚ë‚Å
	SetActiveKeyInput(InputHandle);

	//ˆÈ~‚Ì“ü—Í‚Í‚·‚×‚ÄInputHandle‚És‚­

	//–ˆƒtƒŒ[ƒ€ŽÀs‚ª•K—v‚È‚Ì‚ÅUpdate‚ÉˆÚ“®
#if 0

	while (!ProcessMessage()) {


		//•¶Žš“ü—Í‚ªI—¹‚µ‚Ä‚¢‚é‚È‚çwhileƒ‹[ƒv‚ð”²‚¯‚é
		//if (CheckKeyInput(InputHandle) != 0)break;

		//“ü—Íƒ‚[ƒh‚Ì•`‰æ«o‚È‚¢
		DrawKeyInputModeString(640, 480);
		//«o‚È‚¢
		DrawBox(200, 200, 640, 480, -1, true);

		//«o‚é
		//t2k::debugTrace("\n“ü—Í’†\n");

		//“ü—Í“r’†‚Ì•¶Žš—ñ‚Ì•`‰æ«o‚È‚¢
		DrawKeyInputString(0, 0, InputHandle);

	}

	//“ü—Í‚³‚ê‚½•¶Žš—ñ‚ÌŽæ“¾
	GetKeyInputString(String, InputHandle);

	DeleteKeyInput(InputHandle);
#endif


}

//ƒXƒLƒ‹•t—^ƒCƒxƒ“ƒg‚Í•‰‚Ì’l‚¾‚Á‚½ê‡–³Ž‹‚·‚éƒR[ƒh‚ð–`“ª‚É“ü‚ê‚é

void GameManager::StatusSet(int setType, int value)
{
	//‚à‚µATACKã¸‚³‚¹‚½‚¢‚È‚ç
	//0:ATACK,...

	//int MAGIATACK;	//–‚–@UŒ‚—Í
	//int MAGIDEFENCE;//–‚–@–hŒä—Í
	//int SPEED;		//‘f‘‚³
	//int MIND;		//Œ«‚³
	//int VITALITY;	//Ž‹v—Í
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

/*************Character‚É˜g‚²‚ÆŽÀ‘•‚µ‚½‚½‚ß‚±‚±‚Å‚Í•\Ž¦‚µ‚È‚¢************
//debug
//TrainingScene‚©‚çˆø”‚ÅÀ•W‚ðŽ‚Á‚Ä‚­‚é
void GameManager::CharactorStatusDraw()
{
	int i = 0;
	for (auto c : chara) {
		std::string name = c->charadata->name_;
		int ATK = c->charadata->ATACK;
		int DEF = c->charadata->DEFENCE;
		int MATK = c->charadata->MAGIATACK;
		int MDEF = c->charadata->MAGIDEFENCE;
		int SPEED = c->charadata->SPEED;
		int MIND = c->charadata->MIND;
		int VIT = c->charadata->VITALITY;
		DrawStringEx(500 + i * 200, 200, -1, "–¼‘O:%s", name.c_str());
		DrawStringEx(500 + i * 200, 240, -1, "UŒ‚—Í:%d", ATK);
		DrawStringEx(500 + i * 200, 280, -1, "–hŒä—Í:%d", DEF);
		DrawStringEx(500 + i * 200, 320, -1, "–‚UŒ‚—Í:%d", MATK);
		DrawStringEx(500 + i * 200, 360, -1, "–‚–hŒä—Í:%d", MDEF);
		DrawStringEx(500 + i * 200, 400, -1, "‘¬“x:%d", SPEED);
		DrawStringEx(500 + i * 200, 440, -1, "Œ«‚³:%d", MIND);
		DrawStringEx(500 + i * 200, 480, -1, "Ž‹v—Í:%d", VIT);

		++i;
	}

}
*/

void GameManager::Update()
{
	SceneManager::Update();

	//•¶Žš“ü—Í‚ªI—¹‚µ‚Ä‚¢‚é‚È‚çwhileƒ‹[ƒv‚ð”²‚¯‚é
	if (InputHandle != 0 && CheckKeyInput(InputHandle) != 0) {

		//“ü—Í‚³‚ê‚½•¶Žš—ñ‚ÌŽæ“¾
		GetKeyInputString(String, InputHandle);

		DeleteKeyInput(InputHandle);
		InputHandle = 0;
		//stringŒ^‚É•ÏŠ·
		std::string name(String, sizeof(String) / sizeof(String[0]));
		isInput = false;

		////******debug*****
		//std::string name = "test";


		chara_ = new Chara(name);
		chara.emplace_back(chara_);


	}
	else {


		//“ü—Íƒ‚[ƒh‚Ì•`‰æ«o‚È‚¢
		DrawKeyInputModeString(640, 480);

		//«o‚é
		//t2k::debugTrace("\n“ü—Í’†\n");

		//“ü—Í“r’†‚Ì•¶Žš—ñ‚Ì•`‰æ«o‚È‚¢
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
