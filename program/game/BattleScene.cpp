#include "BattleScene.h"
#include"GameManager.h"
#include"DxLib.h"
#include"Character.h"
#include"Skill.h"
#include"../library/t2klib.h"
#include "../support/Support.h"

extern GameManager* gManager;

BattleScene::BattleScene()
{
	stage_gh = gManager->LoadGraphEx("graphics/blue.png");
	stagetestgh = gManager->LoadGraphEx("graphics/red.png");

	LoadDivGraph("graphics/player_chara_act_right.png", 4, 4, 1, 32, 32, playergh, false);
	LoadDivGraph("graphics/enemy_BattleTest.png", 3, 3, 1, 32, 32, enemyGh, false);

	colorBlack = GetColor(0, 0, 0);
	MyStage.resize(9);
	EnemyStage.resize(9);
	SetStage(MyStage);
	SetStage(EnemyStage);

	//**test テスト用のキャラ作成
	gManager->MakeCharacter("hogehoge", 1);

	//**
}

BattleScene::~BattleScene()
{
}

void BattleScene::Update()
{
	main_sequence_.update(gManager->deitatime_);
}

void BattleScene::Draw()
{
	DrawStage();
	DrawRotaGraph(MyStage[characterPosNum][3], MyStage[characterPosNum][4], 1, 0, playergh[0], true);
	DrawRotaGraph(EnemyStage[enemyPosNum][3], EnemyStage[enemyPosNum][4], 1, 0, enemyGh[0], true);

	for (auto c : gManager->chara) {
		DrawCharaSkill(c);
	}
}

bool BattleScene::Seq_Main(const float deltatime)
{
	//Characterの移動処理
	MoveCharacter();
	//enemyの移動処理
	MoveEnemy();

	//Characterの攻撃処理

	//enemyの攻撃処理


	return true;
}

void BattleScene::ChangeSequence(sequence seq)
{
	nowSeq = seq;
	if (seq == sequence::main) {
		main_sequence_.change(&BattleScene::Seq_Main);
	}
}

void BattleScene::SetStage(std::vector<std::vector<int>> stage)
{
	if (stage == MyStage) {
		for (int i = 0; i < MyStage.size(); ++i) {

			int leftTop_X = myStageStartPos.x + (2 * stageBuf * i + imageSize * i);
			int leftTop_Y = myStageStartPos.y;
			int graphic = stage_gh;

			if (i > 2 && i <= 5) {
				leftTop_X = myStageStartPos.x + (2 * stageBuf * (i - 3) + imageSize * (i - 3));
				leftTop_Y += (2 * stageBuf) + imageSize;
				graphic = stagetestgh;
			}
			else if (i > 5) {
				leftTop_X = myStageStartPos.x + (2 * stageBuf * (i - 6) + imageSize * (i - 6));
				leftTop_Y += (4 * stageBuf) + imageSize * 2;
			}
			int center_X = leftTop_X + stageBuf + (imageSize / 2);
			int center_Y = leftTop_Y + stageBuf + (imageSize / 2);



			MyStage[i].emplace_back(leftTop_X);
			MyStage[i].emplace_back(leftTop_Y);
			MyStage[i].emplace_back(graphic);
			MyStage[i].emplace_back(center_X);
			MyStage[i].emplace_back(center_Y);

		}
	}
	else if (stage == EnemyStage) {
		for (int i = 0; i < EnemyStage.size(); ++i) {

			int leftTop_X = enemyStageStartPos.x + (2 * stageBuf * i + imageSize * i);
			int leftTop_Y = enemyStageStartPos.y;
			int graphic = stage_gh;

			if (i > 2 && i <= 5) {
				leftTop_X = enemyStageStartPos.x + (2 * stageBuf * (i - 3) + imageSize * (i - 3));
				leftTop_Y += (2 * stageBuf) + imageSize;
				graphic = stagetestgh;
			}
			else if (i > 5) {
				leftTop_X = enemyStageStartPos.x + (2 * stageBuf * (i - 6) + imageSize * (i - 6));
				leftTop_Y += (4 * stageBuf) + imageSize * 2;
			}

			int center_X = leftTop_X + stageBuf + (imageSize / 2);
			int center_Y = leftTop_Y + stageBuf + (imageSize / 2);

			EnemyStage[i].emplace_back(leftTop_X);
			EnemyStage[i].emplace_back(leftTop_Y);
			EnemyStage[i].emplace_back(graphic);
			EnemyStage[i].emplace_back(center_X);
			EnemyStage[i].emplace_back(center_Y);
		}
	}
}

void BattleScene::DrawStage()
{
	for (auto mStage : MyStage) {
		DrawRotaGraph(mStage[3], mStage[4], 1, 0, mStage[2], false);
	}
	for (auto eStage : EnemyStage) {
		DrawRotaGraph(eStage[3], eStage[4], 1, 0, eStage[2], false);
	}
}

void BattleScene::MoveCharacter()
{
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_LEFT)) {
		if (characterPosNum % 3 == 0)return;
		characterPosNum -= 1;
	}
	else if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP)) {
		if (characterPosNum <= 2)return;
		characterPosNum -= 3;
	}
	else if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RIGHT)) {
		if (characterPosNum % 3 == 2)return;
		characterPosNum += 1;
	}
	else if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN)) {
		if (characterPosNum >= 6)return;
		characterPosNum += 3;
	}
}

void BattleScene::MoveEnemy()
{
	enemyMoveReCastTime -= gManager->deitatime_;
	if (enemyMoveReCastTime<0) {
		enemyMoveReCastTime = ENEMYMOVERECASTTIMEDEFAULT;
		int rand = GetRand(3);
		if (rand == 0) {
			if (enemyPosNum % 3 == 0)return;
			enemyPosNum -= 1;
		}
		else if (rand == 1) {
			if (enemyPosNum <= 2)return;
			enemyPosNum -= 3;
		}
		else if (rand == 2) {
			if (enemyPosNum % 3 == 2)return;
			enemyPosNum += 1;
		}
		else if (rand == 3) {
			if (enemyPosNum >= 6)return;
			enemyPosNum += 3;
		}
	}
}

void BattleScene::DrawCharaSkill(Chara* c)
{
	for (int i = 0; i < c->charadata->Skill.size(); ++i) {
		DrawStringEx(100, 100 + 20 * i, -1, "%s", c->charadata->Skill[i]->SkillName.c_str());
	}



}
