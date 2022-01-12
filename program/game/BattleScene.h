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

	//�����V�[�N�G���X��ݒ�
	t2k::Sequence<BattleScene*> main_sequence_ =
		t2k::Sequence<BattleScene*>(this, &BattleScene::Seq_Main);


	bool Seq_Main(const float deltatime);

	//�V�[�N�G���X�̗񋓑�
	enum class sequence {
		main,
	};
	sequence nowSeq = sequence::main;

	//Sequence���ړ�������֐�,enum���ꏏ�ɕύX����
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