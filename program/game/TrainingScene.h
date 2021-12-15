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
class Menu;
class MenuWindow;

class TrainingScene : public BaseScene {
public:
	EventManager* eManager = nullptr;
	CharaMenuManager* cMenuManager = nullptr;

	MenuWindow* FrontMenu = nullptr;
	Menu* charaListMenu = nullptr;
	MenuWindow* charaTrainingMenu = nullptr;


	bool changeSceneFlag = false;
	int playergh[4] = {};

	//�V����������̃Z�������֐�
	DayCell* createDayCell(int cellnum);

	//����o�߂���ƈ�Z������������
	void CellDelete();

	//�V�����s���J�[�h�����֐�
	DayCard* createDayCard(int cardEventNum);

	void CardDelete();

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
		{mass_x, 70, 0},
		{mass_x + mass_width * 1, 70, 0},
		{mass_x + mass_width * 2, 70, 0},
		{mass_x + mass_width * 3, 70, 0},
		{mass_x + mass_width * 4, 70, 0},
		{mass_x + mass_width * 5, 70, 0},
		{mass_x + mass_width * 6, 70, 0},
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

	//��						1		2			3		4		5		6			7		8		9		10			11			12		
	std::string month[12] = { "�΂̌�","���̌�","�n�̌�","���̌�","���̌�","���̌�","�ł̌�","��̌�","���̌�","�����̌�","�����̌�","�����̌�" };

	//���̌�
	int now_month = 2;

	std::string days[7] = { "��","��","��","��","��","�y","��" };

	//��T�Ԃ̂ǂ��ɂ��邩
	int week = 0;//1~7
	//���̓�
	int day = 1;//1~30


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

	//���j���[1�`��V�[�N�G���X
	bool Seq_MenuDraw_1(const float deltatime);

	//���j���[2�`��V�[�N�G���X
	bool Seq_MenuDraw_2(const float deltatime);

	//�C�x���g���s�V�[�N�G���X
	bool Seq_DoEvent(const float deltatime);

	bool Seq_EventFrameDraw(const float deltatime);
	//���w���C�x���g�V�[�N�G���X
	bool Seq_NewCharactorComing(const float deltatime);
	//���Ǝ��C�x���g�V�[�N�G���X
	bool Seq_ExitDay(const float deltatime);

	//���n�܂�̋����w��C�x���g�V�[�N�G���X
	bool Seq_SelectEnhance(const float deltatime);

	//�L�����N�^�̋������ڂ�ύX����V�[�N�G���X
	bool Seq_SetEnhance(const float deltatime);
	


	void Update();

	void Draw();    //���j���[��ʁA�w�i�摜�A�^�C�g�������̕`��

private:
	int time_ = 0;
	//���̃V�[�N�G���X��ID
	int sequenceID = 0;
	//�I�𒆂̃J�[�h�̃i���o�[
	int selectNum = 0;

	//0,1,2:�C�x���g���
	int event = 0;
	//�J�[�h�̃C�x���gid
	int size_card = 0;
	//���s�C�x���g�̎c���
	int remainEventNum = 2;

	//�\������Z���̍ő吔
	int cellNum = 7;
	//�\������J�[�h�̍ő吔
	int cardNum = 5;

	int String_Color_Black=0;
	int String_Color_Red = 0;

	int selectedCardPos = 0;
	int selectedCardEvent = 0;
	int selectedCardEventId = 0;

	int buff = 5;
	const int width = 110;

	int enhanceListNameGh = 0;

	Chara* nowChara = nullptr;

	Menu* menu_1 = nullptr;

	Menu* chara_1 = nullptr;

	//�N��
	Menu* yearly = nullptr;
	//�L�������O
	Menu* name = nullptr;
	//�X�^���X
	Menu* stance = nullptr;
	//�����W
	Menu* range = nullptr;
	//�X�e�[�^�X�̖��O
	Menu* menu_3 = nullptr;
	Menu* menu_4 = nullptr;
	Menu* menu_5 = nullptr;
	Menu* menu_6 = nullptr;
	Menu* menu_7 = nullptr;
	Menu* menu_8 = nullptr;
	Menu* menu_9 = nullptr;

	//�X�e�[�^�X�̃����N�ƒl
	Menu* menu_status_1 = nullptr;
	Menu* menu_status_2 = nullptr;
	Menu* menu_status_3 = nullptr;
	Menu* menu_status_4 = nullptr;
	Menu* menu_status_5 = nullptr;
	Menu* menu_status_6 = nullptr;
	Menu* menu_status_7 = nullptr;

	Menu* eventFrame = nullptr;
	Menu* newCharaFrame = nullptr;
	Menu* exitCharaFrame = nullptr;

	Menu* enhanceFrame = nullptr;

	//Menu* charaListTitle = nullptr;
	int charaListTitle_gh = 0;
	int charaListName_gh = 0;

	Menu* charaListWindow = nullptr;

	MenuWindow* enhanceSelect = nullptr;

	
	/*Menu* enhanceButton = nullptr;*/
	
	std::string Log[9] = {};
	//���[�v�����ۂ�
	bool isnowLoop = false;
	//�C�x���g�����t���O����������s���Ȃ����߂̃t���O
	bool doneEvent = false;
	//�N�����ɍŏ��̃C�x���g�������Ă��܂�Ȃ��悤�ɂ��邽�߂̃t���O
	bool doneFirstEvent = false;

	//�{�^���������ꂽ���ǂ���
	bool isClick = false;


	//�V�[�N�G���X�̗񋓑�
	enum class sequence {
		main,
		loop,
		doEvent,
		eventDraw,
		newChara,
		menu_1,
		menu_2,
		menu_3,
		exit,
		selectEnhance,
		Set
	};
	sequence nowSeq = sequence::main;

	void addLog(std::string log);
	void LogDraw();

	void cardSelect();

	//�L�����N�^�[�̃X�e�[�^�X��ʂ�`�悷��֐�
	void DrawWindow();

	//�L�����N�^�[�̋����I����ʂ�`�悷��֐�
	void DrawEnhanceWindow();

	//�L�����N�^�[�̃A�r���e�B�`��֐�
	void DrawAbility(Chara* c);

	void NewCharaWindow();
	//Sequence���ړ�������֐�,enum���ꏏ�ɕύX����
	void ChangeSequence(sequence seq);

	void menuInit();

	


};