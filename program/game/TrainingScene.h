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
class Item;

class TrainingScene : public BaseScene {
public:
	EventManager* eManager = nullptr;
	CharaMenuManager* cMenuManager = nullptr;

	//bool changeSceneFlag = false;
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

	

	//��						1		2			3		4		5		6			7		8		9		10			11			12		
	std::string month[12] = { "�΂̌�","���̌�","�n�̌�","���̌�","���̌�","���̌�","�ł̌�","��̌�","���̌�","�����̌�","�����̌�","�����̌�" };

	//**Debug���͂�����ς���ƃQ�[���J�n���̓��ɂ����ς��**//

	//���̌�
	int now_month = 2;
	//���̓�
	int day = 29;//1~30
	//*******************************************************

	//�j��
	std::string days[7] = { "��","��","��","��","��","�y","��" };

	//��T�Ԃ̂ǂ��ɂ��邩
	int week = 0;//1~7



	//�����V�[�N�G���X��ݒ�
	t2k::Sequence<TrainingScene*> main_sequence_ =
		t2k::Sequence<TrainingScene*>(this, &TrainingScene::Seq_InitSequence);

	TrainingScene();
	~TrainingScene();


	void Update();

	void Draw();    //���j���[��ʁA�w�i�摜�A�^�C�g�������̕`��

	void Save();
	void Load();


private:

	float deltatime_scene = 0;
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

	//�����̐F
	int String_Color_Black = 0;
	int String_Color_Red = 0;

	//��ʂŃA�j���[�V����������L�����N�^�[�̃��X�g
	std::list<Chara*> animChara = {};
	int drawCharaNum[3] = {};

	int rand_cellEvent = 0;

	//�I�΂ꂽ�J�[�h�̏��
	int selectedCardPos = 0;
	int selectedCardEvent = 0;
	int selectedCardEventId = 0;
	//�o�ߓ���
	int passedDay = 0;

	int buff = 5;
	const int width = 110;

	int enhanceListNameGh = 0;

	Chara* nowChara = nullptr;
	Item* nowItem = nullptr;

	Menu* cardWindow = nullptr;
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

	MenuWindow* FrontMenu = nullptr;
	Menu* charaListMenu = nullptr;
	MenuWindow* charaTrainingMenu = nullptr;

	Menu* dayCellFrame = nullptr;
	Menu* teachFrame = nullptr;

	Menu* menuOpenFrame = nullptr;

	Menu* initMessageFrame_1 = nullptr;
	Menu* initMessageFrame_2 = nullptr;

	Menu* initEnterFrame = nullptr;

	//Menu* charaListTitle = nullptr;
	int charaListTitle_gh = 0;
	int charaListName_gh = 0;

	int graduation_gh = 0;

	int enhanceChara_gh = 0;

	int selectCursor_gh = 0;

	int backGround_gh = 0;
	int enter_gh = 0;
	int escape_gh = 0;

	int NewComeDay_gh = 0;
	//�Q�[���J�n����̉摜_1
	int init_gh_1 = 0;
	//�Q�[���J�n����̉摜_2
	int init_gh_2 = 0;

	//init_1�Ŏg�����b�Z�[�W�摜
	int init_Message_gh_1 = 0;
	int init_Message_gh_2 = 0;
	int init_Message_gh_3 = 0;
	int init_Message_gh_4 = 0;

	//���O���b�Z�[�W�w�i
	int logBack_gh = 0;

	int leftArrow_gh[3] = {};
	int rightArrow_gh[3] = {};
	int EnhanceSelectCursor_gh[6] = {};

	//��ԍ��̃}�X�̉摜��x���W
	const float mass_x = 150;
	//�摜�Ԃ̋���(�摜�̑傫����50x50)
	const float mass_width = 130;

	//�}�X�摜��\�����邽�߂̒��S���W
	t2k::Vector3 tbl[7] = {
		{mass_x, 105, 0},
		{mass_x + mass_width * 1, 105, 0},
		{mass_x + mass_width * 2, 105, 0},
		{mass_x + mass_width * 3, 105, 0},
		{mass_x + mass_width * 4, 105, 0},
		{mass_x + mass_width * 5, 105, 0},
		{mass_x + mass_width * 6, 105, 0},
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

	//�A�C�e����ʂ̍��W(����𓮂����Ƒ��̃A�C�e���̘g���S������)
	t2k::Vector3 ItemMenuPos = { 146,0,0 };

	Menu* charaListWindow = nullptr;
	MenuWindow* enhanceSelect = nullptr;

	Menu* selectItemWindow = nullptr;


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

	//�Q�[���J�n����̈�񂾂��s�������t���O
	bool doneInit = false;
	//�ŏ��̐���window�̕`��Ώۂ̕ϐ�
	int drawDescWindow = 0;//0->2

	//�t�F�[�h���t���O ��ł܂Ƃ߂�
	bool nowFade = false;



	//�Q�[���J�n�����񂾂��g���[�j���O�V�[���ōs������
	void InitImageDraw();

	//�����V�[�N�G���X(�Q�[���J�n�����񂫂�̏������s��
	bool Seq_InitSequence(const float deltatime);

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

	//�����A�C�e����`�悷��V�[�N�G���X
	bool Seq_SelectItem(const float deltatime);

	//�A�C�e�����g�p����V�[�N�G���X
	bool Seq_UseItem(const float deltatime);

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
		Set,
		selectItem,
		useItem,
		init
	};
	sequence nowSeq = sequence::init;

	std::vector<std::vector<int>>saveCard = {};

	void addLog(const std::string log);
	void LogDraw();
	//�I�𒆂̃J�[�h���ړ�����֐�
	void cardSelect();

	//�I�𒆂̃J�[�h�̏ڍד��e�������Ă����֐�
	void teachCardRef();
	t2k::Vector3 teach = { 630,450,0 };

	//�e�V�[�N�G���X�̍Ō��ɕ`�悷��֐�
	void DrawBackGround();

	//�L�����N�^�[�̃X�e�[�^�X��ʂ�`�悷��֐�
	void DrawWindow();

	//�L�����N�^�[�̋����I����ʂ�`�悷��֐�
	void DrawEnhanceWindow();

	//�L�����N�^�[�̔\�͒l��SABCD�ŕ\���֐�
	void DrawStatusAlfa(const Chara* c);


	//�\�͒l��SABCD�ɕϊ�����֐�
	int GetStatusAlfa(const int Status);

	//�L�����N�^�[�̃A�r���e�B�`��֐�
	void DrawAbility(const Chara* c);

	void NewCharaWindow();
	//Sequence���ړ�������֐�,enum���ꏏ�ɕύX����
	void ChangeSequence(sequence seq);



	//window�̏��������܂Ƃ߂��֐�
	void menuInit();

	//��ʉ��ŏ����L�������킿��킿�Ⴗ��֐�
	void CharaSpeak();


	////���[�h���̃J�[�h�����p�֐�
	//void LoadCreateCard(int EventType, int EventNum, int PassedDay);
	////���[�h���̃Z�������p�֐�
	//void LoadCreateCell(int EventType);

	//�A�C�e���I����ʂ̃J�[�\���𓮂����֐�
	void selectItem(const int HaveItemNum);
	//�I�𒆂̃A�C�e�����w���ʒu
	int nowSelectNum = 0;
	//�L�����N�^�[�̃����W�ƃX�^���X��`�悷��֐�
	void drawRangeAndStance(const Chara* c);

	//���E�����A�j���[�V����������֐�
	void arrowAnim();
	
	t2k::Vector3 leftArrowPos = { 330,600,0 };

	//�����I����ʂ̃J�[�\���\��(�������̊֐��ƈꏏ�ɂ���)
	void cursorAnim(const int x,const int y);

	//���̃A�j���[�V�����Ɏg���ϐ�
	int ACT_SPEED = 60;
	int act_wait = ACT_SPEED;
	int MAX_MOTION_INDEX = 3;

	int act_index = 0;
	int motion_index_left = 0;
	int motion_index_right = 0;

	//�J�[�\���̃A�j���[�V�����Ɏg���ϐ�
	int ACT_SPEED_CURSOR = 180;
	int act_wait_cursor = ACT_SPEED_CURSOR;
	int MAX_MOTION_INDEX_CURSOR = 6;

	int act_index_cursor = 0;
	int motion_index_cursor = 0;


	//����{�^���摜��`�悷��֐�
	void DrawKeyImage();

	void ReleaseMemory();
};