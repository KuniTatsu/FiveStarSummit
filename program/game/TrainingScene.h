#pragma once
#include"Scene.h"
#include<list>
#include"../library/t2klib.h"

class DayCell;
class DayCard;
class EventManager;
class CharaMenuManager;
class CharaWindow;
class Chara;

class TrainingScene : public BaseScene {
public:
	EventManager* eManager = nullptr;
	CharaMenuManager* cMenuManager = nullptr;


	bool changeSceneFlag = false;
	int playergh[4] = {};

	//�V����������̃Z�������֐�
	DayCell* createDayCell(int cellnum);

	//����o�߂���ƈ�Z������������
	void CellDelete();

	//�V�����s���J�[�h�����֐�
	DayCard* createDayCard(int cardEventNum);

	CharaWindow* createCharaWindow();

	//���ׂẴZ�������Ă������X�g
	std::list<DayCell*> cell_;

	//���ׂẴJ�[�h�����Ă������X�g
	std::list<DayCard*> card_;	
	
	////���ׂẴL�����N�^�[�����Ă������X�g
	//std::list<Chara*> chara_;

	//��ԍ��̃}�X�̉摜��x���W
	const float mass_x = 50;
	//�摜�Ԃ̋���(�摜�̑傫����50x50)
	const float mass_width = 70;

	//�}�X�摜��\�����邽�߂̒��S���W
	t2k::Vector3 tbl[7] = {
		{mass_x, 50, 0},
		{mass_x + mass_width * 1, 50, 0},
		{mass_x + mass_width * 2, 50, 0},
		{mass_x + mass_width * 3, 50, 0},
		{mass_x + mass_width * 4, 50, 0},
		{mass_x + mass_width * 5, 50, 0},
		{mass_x + mass_width * 6, 50, 0},
	};
	//�J�[�h�̈�ԍ��̉摜��x���W
	const float card_x = 400;
	//�摜���̋���(�摜�̑傫����40x80)
	const float card_width = 120;

	//�J�[�h��\�����邽�߂̒��S���W
	t2k::Vector3 cardtbl[5] = {
		{card_x, 620, 0},
		{card_x + card_width * 1, 620, 0},
		{card_x + card_width * 2, 620, 0},
		{card_x + card_width * 3, 620, 0},
		{card_x + card_width * 4, 620, 0},

	};

	

	//�����V�[�N�G���X��ݒ�
	t2k::Sequence<TrainingScene*> main_sequence_ =
		t2k::Sequence<TrainingScene*>(this, &TrainingScene::Seq_Training_Main);

	TrainingScene();
	~TrainingScene();

	//���C���V�[�N�G���X �e�����ֈڍs����
	bool Seq_Training_Main(const float deltatime);

	//�I�������J�[�h��������܂ł̃V�[�N�G���X
	bool Seq_CardDisappear(const float deltatime);


	//�����o�ߒ��̃V�[�N�G���X ���[�v�J�E���g��0�ɂȂ�܂ŌJ��Ԃ� ���[�v�J�E���g:�o�ߓ���
	bool Seq_LoopDay(const float deltatime);

	int loopdaycount = 0;




	void Update();

	void Draw();    //���j���[��ʁA�w�i�摜�A�^�C�g�������̕`��

private:
	int time_ = 0;
	int sequenceID = 0;
	int selectNum = 0;

	int cellNum = 7;
	int cardNum = 5;

	std::string Log[9] = {};
	//���[�v�����ۂ�
	bool isnowLoop = false;
	//�C�x���g�����t���O����������s���Ȃ����߂̃t���O
	bool doneEvent = false;
	//�N�����ɍŏ��̃C�x���g�������Ă��܂�Ȃ��悤�ɂ��邽�߂̃t���O
	bool doneFirstEvent = false;

	void addLog(std::string log);
	void LogDraw();

	void cardSelect();

	//�L�����N�^�[�̃X�e�[�^�X��ʂ�`�悷��֐�
	void DrawWindow();

};