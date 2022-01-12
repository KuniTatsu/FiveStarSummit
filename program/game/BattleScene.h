#pragma once
#include"Scene.h"
#include"../library/t2klib.h"
#include<vector>
#include<string>


class BattleScene : public BaseScene {
public:

	bool changeSceneFlag = false;
	int encountrand = 0;

	BattleScene();
	~BattleScene();



	void Update();

	void Draw();

private:

	int stage_gh = 0;
	int stagetestgh = 0;

	int colorBlack = 0;

	int playergh[4] = {};

	//初期シークエンスを設定
	t2k::Sequence<BattleScene*> main_sequence_ =
		t2k::Sequence<BattleScene*>(this, &BattleScene::Seq_Main);


	bool Seq_Main(const float deltatime);

	//シークエンスの列挙体
	enum class sequence {
		main,
	};
	sequence nowSeq = sequence::main;

	//Sequenceを移動させる関数,enumも一緒に変更する
	void ChangeSequence(sequence seq);

	
	std::vector<std::vector<int>> MyStage;
	std::vector<std::vector<int>> EnemyStage;

	const int stageBuf = 10;
	const int imageSize = 50;

	t2k::Vector3 myStageStartPos = { 200,200,0 };
	t2k::Vector3 enemyStageStartPos = { 450,200,0 };

	void SetStage(std::vector<std::vector<int>> stage);
	//int SetGraphic();

	void DrawStage();


	int characterPosNum = 0;
	void MoveCharacter();

};