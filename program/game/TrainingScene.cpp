#include "TrainingScene.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "DayCell.h"
#include<time.h>
#include"EventManager.h"
#include <iostream>
#include"GameManager.h"
#include"Event.h"
#include"CardEvent.h"
#include"DayCard.h"
#include"CharaMenuManager.h"
#include"CharaWindow.h"
#include"Character.h"
#include"MenuWindow.h"
#include"Ability.h"
#include"ExtraEvent.h"
#include"ForceStopDay.h"
#include"MenuWindow.h"
//#include"AbilityManager.h"

extern GameManager* gManager;


TrainingScene::TrainingScene()
{
	eManager = new EventManager();
	cMenuManager = new CharaMenuManager();

	eventFrame = new Menu(200, 100, 500, 300, "graphics/WindowBase_02.png");
	newCharaFrame = new Menu(200, 100, 700, 500, "graphics/WindowBase_02.png");
	exitCharaFrame = new Menu(200, 100, 700, 500, "graphics/WindowBase_02.png");


	enhanceFrame = new Menu(146, 0, 650, 743, "graphics/WindowBase_02.png");
	//enhanceButton = new Menu(0, 0, 200, 100, "graphics/WindowBase_02.png");

	MenuWindow::MenuElement_t* menu_0 = new MenuWindow::MenuElement_t[]{
		{40,50,"��␶�ꗗ",0},
		{40,100,"�P�����e�ꗗ",1},
		{40,150,"�e�X�g2",2},
		{40,200,"�e�X�g3",3},
		{40,250,"�e�X�g4",4}
	};
	// ���j���[�E�B���h�E�̃C���X�^���X��
	FrontMenu = new MenuWindow(16, 0, 130, 300, "graphics/WindowBase_02.png", menu_0, 5);

	charaListMenu = new Menu(FrontMenu->menu_x + FrontMenu->menu_width + 10, FrontMenu->menu_y, 650, 743, "graphics/WindowBase_02.png");
	cMenuManager->StatusMenuPos.x = charaListMenu->menu_x + (charaListMenu->menu_width / 2);

	MenuWindow::MenuElement_t* enhance = new MenuWindow::MenuElement_t[]{
		{40,50,"���܂�������",0},
		{40,100,"�U������",1},
		{40,150,"�h�䋭��2",2},
		{40,200,"���@�U������3",3},
		{40,250,"���@�h�䋭��",4},
		{40,300,"�f��������",5},
		{40,350,"��������",6},
		{40,400,"���v�͋���",7},
	};
	enhanceSelect = new MenuWindow(300, 100, 100, 300, "graphics/WindowBase_02.png", enhance, 8);


	SRand(time(0));

	String_Color_Black = GetColor(0, 0, 0);
	String_Color_Red = GetColor(255, 0, 0);


	//�v���C���[�摜�̃��[�h
	LoadDivGraph("graphics/player_chara_act_right.png", 4, 4, 1, 32, 32, playergh, false);

	charaListTitle_gh = gManager->LoadGraphEx("graphics/enhanceWindow.png");
	charaListName_gh = gManager->LoadGraphEx("graphics/charaListName.png");

	enhanceListNameGh = gManager->LoadGraphEx("graphics/charaEnhanceName.png");


	//�ŏ���7���X�g�ɓ���鏈��������
	for (int k = 0; k < cellNum; ++k) {
		int random = GetRand(15);
		createDayCell(random);
	}
	for (int k = 0; k < cardNum; ++k) {
		int random = GetRand(15);
		createDayCard(random);
	}
	//Debug

	/*createCharaWindow();
	createCharaWindow();*/
	//

	//2�N,3�N�̐�y�𐶐�
	eManager->exEvent->NewMemberComing(3);
	eManager->exEvent->NewMemberComing(2);
}

TrainingScene::~TrainingScene()
{
	delete eManager;
}

//�����J�[�h���I�΂��܂ł̃V�[�N�G���X(�����ړ��ς�)
bool TrainingScene::Seq_Training_Main(const float deltatime)
{
	//loopdaycount��0�łȂ���΃V�[�N�G���X��LoopDay�ɂ���
	//loopdaycount��0�ɂȂ�����cell_���X�g��3�Ԗڂ̃C�x���g��ǂݍ���	

	if (main_sequence_.isStart()) {
		sequenceID = 0;
	}
	cardSelect();
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		FrontMenu->Open();
		//���j���[��������V�[�N�G���X�Ɉړ�����
		ChangeSequence(sequence::menu_1);
		return true;
	}
	//���[�v���������肷�鏊
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_NUMPAD0) && isnowLoop == false) {
		isnowLoop = true;
		doneFirstEvent = true;
		doneEvent = false;

		//���ݑI�𒆂̃J�[�h�̌o�ߓ�����ǂݍ���
		//loopdaycount�ɑ��
		int c = 0;
		for (auto card : card_) {
			if (c == selectNum)
			{
				loopdaycount = card->passedDayNum;
				card->isSelected = true;
				selectedCardPos = selectNum;
				selectedCardEvent = card->cardEventTypeId;
				selectedCardEventId = card->cardEventId;
			}
			c++;
		}
		CardDelete();
		addLog(std::to_string(loopdaycount) + "���o�߂����");
		//day += loopdaycount;


		int randomnum = GetRand(15);
		createDayCard(randomnum);

		//�J�[�h�������オ��A�g�債�Ĉ��ȏ�̑傫���ɂȂ�Ə�����V�[�N�G���X���͂��݂���
		//main_sequence_.change(&TrainingScene::Seq_CardDisappear);
		ChangeSequence(sequence::loop);
		//main_sequence_.change(&TrainingScene::Seq_LoopDay);
		return true;
	}


	//DrawStringEx(200, 350, -1, "Seq_Training_Main");
	//���[�v���������Ƀ��[�v���J�n���A0�ɂȂ�܂ł��������
	if (loopdaycount != 0)
	{

		//����o�߂���Ԋu
		time_++;
		if (time_ > 40) {
			time_ = 0;
			ChangeSequence(sequence::loop);
			//main_sequence_.change(&TrainingScene::Seq_LoopDay);

		}
	}
	else {
		//���������ړ������Ă��Ȃ��Ȃ�C�x���g���s��Ȃ�
		if (doneFirstEvent == false)return true;
		//std::list<DayCell*>::iterator it = cell_.begin();
		//
		//++it;
		//++it;//iterator��3�ԖڂɈړ�

		if (doneEvent == false) {
			std::list<DayCell*>::iterator it = cell_.begin();

			++it;
			++it;//iterator��3�ԖڂɈړ�
			//������Z���̃C�x���g��ǂݍ���
			event = (*it)->eventID;
			//���s����C�x���g�̑����������ꓮ�I�ɕς��
			remainEventNum = 2;

			//DoEvent�Ɉړ�
			ChangeSequence(sequence::doEvent);
			//main_sequence_.change(&TrainingScene::Seq_DoEvent);

		}

		isnowLoop = false;

		/*if (day > 30) {
			day = 1;
			now_month = (now_month + 1) % 12;
		}*/




	}
	return true;
}

//**********************Seq_CardDisapper*****************************//
bool TrainingScene::Seq_CardDisappear(const float deltatime)
{
	//�J�[�h��傫������
	int c = 0;
	for (auto card : card_) {
		if (c == selectNum)
		{

			if (card->isSelected == true) {
				float timecount = 0;

				while (card->exRate <= 5.0)
				{
					timecount++;
					if (timecount < 40)continue;
					card->exRate += 0.01;
					timecount = 0;

				}
			}
		}
		c++;
	}

	t2k::debugTrace("\n�J�[�h�̊g�又�����I���܂���\n");
	//�J�[�h������
	//�V�����J�[�h�𐶐�����
	//���X�g�ɓ����
	ChangeSequence(sequence::loop);

	//main_sequence_.change(&TrainingScene::Seq_LoopDay);
	return true;
}

//**********************Seq_LoopDay**********************************//
//�����J�[�h���I�΂ꂽ���Ƃ̃V�[�N�G���X(�����ړ�)
bool TrainingScene::Seq_LoopDay(const float deltatime)
{

	if (main_sequence_.isStart()) {
		sequenceID = 1;

	}
	//������DayCell��ǉ�������������肷�鏈��������
	//�V����1��DayCell�����
	int random = GetRand(15);


	//���w�����d����
	if (now_month == 3 && day == 1) {
		createDayCell(16);
	}
	//���Ǝ����d����
	else if (now_month == 2 && day == 9) {
		createDayCell(17);
	}
	else {
		createDayCell(random);
	}
	std::list<DayCell*>::iterator it = cell_.begin();

	++it;
	++it;
	++it;

	//DayCell* p = new DayCell(0);
	//���X�g��1�Ԃ����X�g����O����delete���鐶��
	CellDelete();

	//���������K���~�܂���Ȃ�loopdaycount��0�ɂ���
	bool isForcedStopDay = false;


	for (auto stopday : eManager->ForcedStopDayList) {

		//���̓��ɂ����K���~�܂����������
		if ((*it)->myMonth == stopday->month && (*it)->myDay == stopday->day) {
			loopdaycount = 0;
			//�ǂ̋�����~�C�x���g��
			if (stopday->id == 100) {
				isForcedStopDay = true;
				doneEvent = true;
				ChangeSequence(sequence::newChara);

				//main_sequence_.change(&TrainingScene::Seq_NewCharactorComing);

				break;
			}
			else if (stopday->id == 103) {
				isForcedStopDay = true;
				doneEvent = true;
				ChangeSequence(sequence::exit);
				break;
			}
			//���n�܂�̓����������U�������ڂ�I�ԃV�[�N�G���X�ɔ�΂�
			else if (stopday->id >= 900) {
				isForcedStopDay = true;

				ChangeSequence(sequence::selectEnhance);

				break;
			}
			//main_sequence_.change(&TrainingScene::Seq_NewCharactorComing);
		}

	}
	//���̃t���[���Ɉړ�����
	if (isForcedStopDay)return true;

	loopdaycount--;

	ChangeSequence(sequence::main);

	//main_sequence_.change(&TrainingScene::Seq_Training_Main);
	return true;
}

bool TrainingScene::Seq_MenuDraw_1(const float deltatime)
{
	if (FrontMenu->SelectNum == 0 && t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		//menu�̏㉺�𑀍�o���Ȃ�����
		FrontMenu->manageSelectFlag = false;

		//menu2�V�[�N�G���X�Ɉړ�����
		ChangeSequence(sequence::menu_2);
		return true;
	}
	else if (FrontMenu->SelectNum == 1 && t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {

		//menu�̏㉺�𑀍�o���Ȃ�����
		FrontMenu->manageSelectFlag = false;

		//selectEnhance�V�[�N�G���X�Ɉړ�����
		ChangeSequence(sequence::selectEnhance);
		return true;
	}



	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {
		FrontMenu->menu_live = false;
		//���C���V�[�N�G���X�Ɉړ�����
		ChangeSequence(sequence::main);
		return true;
	}



	return true;
}

bool TrainingScene::Seq_MenuDraw_2(const float deltatime)
{
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_UP)) {
		if (cMenuManager->StatusMenuPos.y < 75)
			cMenuManager->StatusMenuPos.y += 10;
	}
	else if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_DOWN)) {
		cMenuManager->StatusMenuPos.y -= 10;
	}

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {


		//menu1�V�[�N�G���X�Ɉړ�����
		FrontMenu->manageSelectFlag = true;
		cMenuManager->PosReset();
		ChangeSequence(sequence::menu_1);
		return true;
	}



	return true;
}

bool TrainingScene::Seq_DoEvent(const float deltatime)
{
	int size = 0;
	int rand_cellEvent = 0;
	//int rand_cardEvent = 0;

	//�C�x���g����������V�[�N�G���X
	//�C�x���g�̉摜��\��
	//�C�x���g�̓��e�𕶏͂ŕ\��
	if (main_sequence_.isStart()) {
		sequenceID = 2;
		if (event == 99) {
			rand_cellEvent = 99;
		}
		else {
			size = eManager->eventList[event].size();
			//size_card = eManager->eventList[selectedCardEvent].size();

			rand_cellEvent = GetRand(size - 1);
			//rand_cardEvent = GetRand(size_card - 1);
		}
	}

	//�C�x���g�����V�[���̃E�B���h�E���o��
	//�E�B���h�E�����b�Z�[�W��ǂ�
	//�Ȃɂ��̃L�[�������̓N���b�N�ŃE�B���h�E������
	//���̃E�B���h�E�̓C�x���g���ƂɊJ��
	if (sequenceID == 3)return true;
	if (remainEventNum == 2) {
		//�C�x���g1�̎��s����
		t2k::debugTrace("\n�Z���̃C�x���g��:%d,%d\n", event, rand_cellEvent);

		eManager->DoEvent(event, rand_cellEvent);

		sequenceID = 3;
		ChangeSequence(sequence::eventDraw);

		//main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
		return true;

	}
	else if (remainEventNum == 1) {
		//�C�x���g��2���s����
		t2k::debugTrace("\n�J�[�h�̃C�x���g��:%d,%d\n", selectedCardEvent, selectedCardEventId);

		eManager->DoCardEvent(selectedCardEvent, selectedCardEventId);

		//eManager->DoEvent(selectedCardEvent, selectedCardEventId);
		sequenceID = 3;
		t2k::debugTrace("\n�C�x���g2�߂̉�ʏ���\n");

		ChangeSequence(sequence::eventDraw);

		//main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
		return true;

	}
	//�N�����C�x���g�̓��e�����O�ŏo�͂�����
	//Debug
	//*************cellEvent�̃��O�\��**************
	addLog("�Z���̃C�x���gid��" + std::to_string(event) + ',' + std::to_string(rand_cellEvent));
	if (eManager->eventList[event][rand_cellEvent]->num_ > 0) {
		addLog(eManager->eventList[event][rand_cellEvent]->StatusName_ + "��" + std::to_string(eManager->eventList[event][rand_cellEvent]->num_) + "��������");
	}
	else {
		int hoge = eManager->eventList[event][rand_cellEvent]->num_ * (-1);
		addLog(eManager->eventList[event][rand_cellEvent]->StatusName_ + "��" + std::to_string(hoge) + "��������");
	}
	//*************cardEvent�̃��O�\��**************
	addLog("�J�[�h�̃C�x���gid��" + std::to_string(selectedCardEvent) + ',' + std::to_string(selectedCardEventId));

	{

		int i = 0;
		//�X�e�[�^�X�ω����������Ώۃ��X�g�𑍂Ȃ�
		for (auto hoge : eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusName) {
			//�������̕ω������X�e�[�^�X���v���X��������
			if (eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusValue[i] > 0) {

				addLog(eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusName[i] + "��" +
					std::to_string(eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusValue[i]) + "��������");
				i++;
			}
			//�������̕ω������X�e�[�^�X���}�C�i�X��������
			else {
				int num = eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusValue[i] * (-1);

				addLog(eManager->cardEventList[selectedCardEvent][selectedCardEventId]->changeStatusName[i] + "��"
					+ std::to_string(num) + "��������");
			}
		}

	}


	//�����A�r���e�B���ǉ������C�x���g�����s����Ă�����
	if (eManager->cardEventList[selectedCardEvent][selectedCardEventId]->AbilityType != -1) {
		int abitype = eManager->cardEventList[selectedCardEvent][selectedCardEventId]->AbilityType;
		int abiid = eManager->cardEventList[selectedCardEvent][selectedCardEventId]->AbilityId;
		//�ǂ̃A�r���e�B���ǉ����ꂽ�����O���擾
		std::string hoge = gManager->GetAbility(abitype, abiid);
		std::string addedAbilityName = "";
		for (auto c : gManager->chara) {
			if (c->recentAddedAbility.empty())continue;
			addedAbilityName = c->recentAddedAbility;
			//���܂����O�\������Ȃ�
			addLog(c->charadata->name_ + "��" + addedAbilityName + "���K�������B");
		}

	}

	doneEvent = true;

	//���߂Œǉ����ꂽ�A�r���e�B��������������@
	for (auto c : gManager->chara) {
		if (c->recentAddedAbility.empty()) continue;
		c->recentAddedAbility = c->recentAddedAbility.erase(0);

	}
	ChangeSequence(sequence::main);

	//main_sequence_.change(&TrainingScene::Seq_Training_Main);

	return true;
}

bool TrainingScene::Seq_EventFrameDraw(const float deltatime)
{

	//�C�x���g1�̕`�揈�� 
	if (main_sequence_.isStart()) {

		eventFrame->menu_live = true;
	}

	eventFrame->Menu_Draw();

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		remainEventNum--;
		eventFrame->menu_live = false;

		ChangeSequence(sequence::doEvent);

		//main_sequence_.change(&TrainingScene::Seq_DoEvent);
	}

	return true;
}

bool TrainingScene::Seq_NewCharactorComing(const float deltatime)
{
	if (main_sequence_.isStart()) {

		newCharaFrame->menu_live = true;
		eManager->exEvent->NewMemberComing(1);
		t2k::debugTrace("\n���w���C�x���g���s\n");
	}
	//eventframe->Menu_Draw();

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {

		newCharaFrame->menu_live = false;
		ChangeSequence(sequence::main);

		//main_sequence_.change(&TrainingScene::Seq_Training_Main);
	}

	return true;
}

bool TrainingScene::Seq_ExitDay(const float deltatime)
{
	if (main_sequence_.isStart()) {
		eManager->exEvent->ExitMember();
	}


	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {


		ChangeSequence(sequence::main);

	}
	return true;
}

bool TrainingScene::Seq_SelectEnhance(const float deltatime)
{

	//�L�������Ƃ̋����w��X�e�[�^�X��I�ԉ�ʂ��o��

	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_UP)) {
		if (cMenuManager->StatusMenuPos.y < 75)
			cMenuManager->StatusMenuPos.y += 10;
	}
	else if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_DOWN)) {
		cMenuManager->StatusMenuPos.y -= 10;
	}


	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {


		//menu1�V�[�N�G���X�Ɉړ�����
		FrontMenu->manageSelectFlag = true;
		cMenuManager->PosReset();
		ChangeSequence(sequence::menu_1);
		return true;
	}
	//*****window�̈ʒu�ύX����*****//

	int i = 0;
	if (gManager->chara.empty() == false) {
		for (auto c : gManager->chara) {

			c->cWindow->windowPos.x = cMenuManager->StatusMenuPos.x;

			c->cWindow->windowPos.y = cMenuManager->StatusMenuPos.y + (20 * (i + 1)) + ((cMenuManager->CharaWindowHeight) * (i));
			i++;
			c->changeWindowPos(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2), c->cWindow->windowPos.y, 1);
			//�{�^���̍��W�ύX
			c->enhanceButton->menu_x = cMenuManager->StatusMenuPos.x + 150;
			c->enhanceButton->menu_y = c->cWindow->windowPos.y + 100;

			if (t2k::Input::isMouseTrigger(t2k::Input::MOUSE_RELEASED_LEFT)) {
				int x; int y;
				GetMousePoint(&x, &y);
				if (x >= c->enhanceButton->menu_x && x <= c->enhanceButton->menu_x + 140
					&& y >= c->enhanceButton->menu_y && y <= c->enhanceButton->menu_y + 50) {

					DrawStringEx(100, 100, -1, "hoge");
					t2k::debugTrace("hogeee");
					////�N���b�N���ꂽ���Ƃ��擾
					//bool isClick = true;

					//���̃L�����N�^���擾
					nowChara = c;

					enhanceSelect->menu_live = true;

					//�V�[�N�G���X���ړ�
					ChangeSequence(sequence::Set);
					break;

				}
			}
		}
	}





	return true;
}

bool TrainingScene::Seq_SetEnhance(const float deltatime)
{
	//�������ڂ�I�ԏ���
	// 
	//�I�яI��������Ɩ߂鏈��
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_ESCAPE)) {


		//menu1�V�[�N�G���X�Ɉړ�����
		enhanceSelect->menu_live = false;
		ChangeSequence(sequence::selectEnhance);
		return true;
	}
	return true;
}

DayCell* TrainingScene::createDayCell(int cellnum) {

	//cellnum:0����,1����,2����
	DayCell* new_obj = new DayCell(cellnum);

	//DayCell���̂�eventID�����肷��
	new_obj->eventID = eManager->setEvent(cellnum);
	//DayCell�Ɏ����̓��ɂ�����������
	new_obj->myDayName = days[week];
	new_obj->myDay = day;
	new_obj->myMonthName = month[now_month];
	new_obj->myMonth = now_month;

	//�������ɂ�������̓��ɂ���������

	//ForcedStopFlag��true�ɂ���



	//���ɂ��̍X�V����
	day++;
	week = (week + 1) % 7;

	//����31�ȏ�ɂȂ��Ă����玟�̌��ɂ���
	if (day > 30) {
		day = 1;
		now_month = (now_month + 1) % 12;
	}

	cell_.emplace_back(new_obj);
	return new_obj;
}

void TrainingScene::CellDelete()
{
	//���X�g��1�Ԗڂ�cell�����X�g����O��
	//cell_.pop_front();

	std::list<DayCell*>::iterator it = cell_.begin();
	(*it)->is_alive_ = false;
	cell_.erase(it);
}

DayCard* TrainingScene::createDayCard(int cardEventNum)
{
	DayCard* new_card = new DayCard(cardEventNum);
	//�o�ߓ����������_���Ō���
	int daynum = GetRand(4) + 1;
	new_card->passedDayNum = daynum;

	//�J�[�h��y���W������
	new_card->pos_.y = 620;

	//�C�x���g�^�C�v0,1,2������
	new_card->cardEventTypeId = eManager->setEvent(cardEventNum);

	size_card = eManager->eventList[new_card->cardEventTypeId].size();
	//�C�x���g�^�C�v�̒������������_���Ō���
	new_card->cardEventId = GetRand(size_card - 1);

	card_.emplace_back(new_card);

	return new_card;
}

void TrainingScene::CardDelete()
{
	//�I�𒆂̃J�[�h������
	std::list<DayCard*>::iterator it = card_.begin();
	for (auto card : card_) {
		if (card->isSelected == true)
		{
			card->is_alive_ = false;
			//std::list<DayCard*>::iterator it = card_.begin();
			for (int i = 0; i < selectedCardPos; ++i) {
				if (selectedCardPos == 0)break;
				it++;
			}
		}
	}

	card_.erase(it);
}

CharaWindow* TrainingScene::createCharaWindow()
{
	CharaWindow* new_charaWindow = new CharaWindow();
	cMenuManager->AddList(new_charaWindow);

	return new_charaWindow;
}


//�V�[�N�G���X�Ɉˑ����Ȃ��V�[�����̑S�ʏ����������ōs��
void TrainingScene::Update()
{
	main_sequence_.update(gManager->deitatime_);


	//�b��I�ȃL�����쐬
	//if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE)) {

	//	gManager->MakeCharacter("", 1);

	//	//�o�͗��Ƀ��b�Z�[�W�o�������񂾂��Ǐo�Ȃ��񂾂��ǁI
	//	//std::cout << "�L�������쐬����܂���" << std::endl;
	//	t2k::debugTrace("\n�L�������쐬����܂���\n");
	//}



	//--------------debug end------------------------//

	for (auto hoge : cell_) {
		if (hoge->is_alive_ == false) {
			delete hoge;
		}
	}
	for (auto hoge : card_) {
		if (hoge->is_alive_ == false) {
			delete hoge;
		}
	}
}

void TrainingScene::Draw()
{
	int i = 0;
	for (auto cell : cell_) {
		cell->pos_ = tbl[i++];
		cell->Draw();
	}
	int hogehoge = 0;
	for (auto card : card_) {
		card->pos_.x = cardtbl[hogehoge++].x;
		card->Draw();

	}
	//cardSelect();
	//DrawWindow();

	DrawStringEx(900, 150, -1, "%s", month[now_month].c_str());


	//------debug------
	int k = 0;
	for (auto c : cell_) {

		DrawStringEx(50, 400 + k * 50, -1, "%d", c->eventID);
		++k;
	}
	DrawStringEx(100, 300, -1, "%d", loopdaycount);


	if (nowSeq == sequence::main) {
		DrawStringEx(100, 350, -1, "SeqTrainingMain");
	}
	else if (nowSeq == sequence::loop) {
		DrawStringEx(100, 350, -1, "SeqLoopDay");
	}
	else if (nowSeq == sequence::doEvent) {
		DrawStringEx(100, 350, -1, "SeqDoEvent");
	}
	else if (nowSeq == sequence::eventDraw) {
		DrawStringEx(100, 350, -1, "SeqDrawEventFrame");
	}
	else if (nowSeq == sequence::newChara) {
		DrawStringEx(100, 350, -1, "SeqNewChara");
	}
	else if (nowSeq == sequence::menu_1) {
		DrawStringEx(100, 350, -1, "SeqMenu1");
	}
	else if (nowSeq == sequence::selectEnhance) {
		DrawStringEx(100, 350, -1, "SeqSelectEnhance");
	}

	DrawStringEx(100, 400, -1, "�C�x���gID��%d", eManager->eventdebugID);

	DrawRotaGraph(190, 70, 1, 0, playergh[2], true);
	//--------------------

	LogDraw();

	//cMenuManager->DrawWindow();

	//�������̃V�[�N�G���X���Z�Z�Ȃ�`�悷��
	if (nowSeq == sequence::newChara) {

		newCharaFrame->Menu_Draw();
	}
	else if (nowSeq == sequence::exit) {
		exitCharaFrame->Menu_Draw();

	}
	else if (nowSeq == sequence::menu_1 || nowSeq == sequence::menu_2 || nowSeq == sequence::selectEnhance) {
		FrontMenu->All();
	}

	if (nowSeq == sequence::menu_2) {
		//DrawBox(5, 5, 800, 600, -1, true);
		charaListMenu->Menu_Draw();
		DrawWindow();
		DrawStringEx(300, 300, String_Color_Black, "������menu2����");

		DrawRotaGraph(charaListMenu->menu_x + (charaListMenu->menu_width / 2), charaListMenu->menu_y + 35, 0.5, 0, charaListTitle_gh, false);
		DrawRotaGraph(charaListMenu->menu_x + (charaListMenu->menu_width / 2), charaListMenu->menu_y + 35, 0.5, 0, charaListName_gh, true);
		//DrawStringEx(charaListMenu->menu_x + (charaListMenu->menu_width / 2), charaListMenu->menu_y + 35, String_Color_Red, "�`���Ҍ�␶�ꗗ");
	}
	else if (nowSeq == sequence::selectEnhance) {

		enhanceFrame->Menu_Draw();

		DrawEnhanceWindow();

		DrawRotaGraph(enhanceFrame->menu_x + (enhanceFrame->menu_width / 2), enhanceFrame->menu_y + 35, 0.5, 0, charaListTitle_gh, false);
		DrawRotaGraph(enhanceFrame->menu_x + (enhanceFrame->menu_width / 2), enhanceFrame->menu_y + 35, 0.5, 0, enhanceListNameGh, true);
	}
	else if (nowSeq == sequence::Set) {
		enhanceSelect->All();
	}

	//if (gManager->isInput== true) {
	//	//���̓��[�h�̕`��
	//	DrawKeyInputModeString(640, 480);

	//	//���͓r���̕�����̕`��
	//	DrawKeyInputString(0, 0, gManager->InputHandle);
	//}
}

//7�܂Ń��O�𐶐�����֐�,�Â������������
void TrainingScene::addLog(std::string log)
{
	if (!Log[8].empty()) {
		Log[0] = Log[1];
		Log[1] = Log[2];
		Log[2] = Log[3];
		Log[3] = Log[4];
		Log[4] = Log[5];
		Log[5] = Log[6];
		Log[6] = Log[7];
		Log[7] = Log[8];
		Log[8] = log;
		return;
	}
	for (int i = 0; i < 10; i++) {

		if (Log[i].empty()) {

			Log[i] = log;
			return;
		}
	}

}
//�����������O��\������֐�
void TrainingScene::LogDraw()
{
	for (int i = 0; i < 9; ++i) {
		DrawStringEx(100, 500 + (i * 20), -1, "%s", Log[i].c_str());
	}
}

void TrainingScene::cardSelect()
{
	//���E�L�[�őI�𒆂̃J�[�h��ς��鏈��������

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RIGHT)) {
		selectNum = (selectNum + 1) % 5;
	}
	else if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_LEFT)) {
		selectNum = (selectNum + 4) % 5;
	}

	int c = 0;
	for (auto card : card_) {
		if (c == selectNum) {
			card->pos_.y = 600;
		}
		else {
			card->pos_.y = 620;
		}
		c++;
	}


}



void TrainingScene::DrawWindow()
{
	//Charactor* p = nullptr;

	int i = 0;
	if (gManager->chara.empty())return;
	for (auto c : gManager->chara) {

		c->cWindow->windowPos.x = cMenuManager->StatusMenuPos.x;

		c->cWindow->windowPos.y = cMenuManager->StatusMenuPos.y + (20 * (i + 1)) + ((cMenuManager->CharaWindowHeight) * (i));

		i++;

		c->changeWindowPos(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2), c->cWindow->windowPos.y, 0);
		c->charaListWindow->Menu_Draw();



		std::string name = c->charadata->name_;
		int year = c->charadata->stayYear;
		int ATK = c->charadata->ATACK;
		int DEF = c->charadata->DEFENCE;
		int MATK = c->charadata->MAGIATACK;
		int MDEF = c->charadata->MAGIDEFENCE;
		int SPEED = c->charadata->SPEED;
		int MIND = c->charadata->MIND;
		int VIT = c->charadata->VITALITY;

		int ATK_exp = c->charadata->EXP_ATACK;
		int DEF_exp = c->charadata->EXP_DEFENCE;
		int MATK_exp = c->charadata->EXP_MAGIATACK;
		int MDEF_exp = c->charadata->EXP_MAGIDEFENCE;
		int SPEED_exp = c->charadata->EXP_SPEED;
		int MIND_exp = c->charadata->EXP_MIND;
		int VIT_exp = c->charadata->EXP_VITALITY;


		std::string abi1 = {};
		//�A�r���e�B������Ύ擾
		//�����I�ɂ͂��ׂĂ̎����Ă���A�r���e�B��\��������悤�ɕύX����

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 200, c->cWindow->windowPos.y + 10, String_Color_Black, "�A�r���e�B:");


		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 10, String_Color_Black, "���O:%s", name.c_str());

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 30, String_Color_Black, "�w�N:%d�N", year);

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 70, String_Color_Black, "�U����:%d", ATK);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 90, String_Color_Black, "�h���:%d", DEF);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 110, String_Color_Black, "���@�U����:%d", MATK);

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 130, String_Color_Black, "���@�h���:%d", MDEF);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 150, String_Color_Black, "���x:%d", SPEED);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 170, String_Color_Black, "����:%d", MIND);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 190, String_Color_Black, "���v��:%d", VIT);

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 50, String_Color_Black, "�U���͌o���l:%d", ATK_exp);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 70, String_Color_Black, "�h��͌o���l:%d", DEF_exp);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 90, String_Color_Black, "���U���͌o���l:%d", MATK_exp);
		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 160, c->cWindow->windowPos.y + 110, String_Color_Black, "���h���:%d", MDEF_exp);


		//DrawGraph(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 50, c->cWindow->windowPos.y + 10, c->gh[2], false);
		DrawRotaGraph(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 170, c->cWindow->windowPos.y + 20, 1, 0, c->gh[1], true);

		DrawAbility(c);


	}

}

void TrainingScene::DrawEnhanceWindow()
{
	//int i = 0;
	if (gManager->chara.empty())return;
	for (auto c : gManager->chara) {

		/*c->cWindow->windowPos.x = cMenuManager->StatusMenuPos.x;

		c->cWindow->windowPos.y = cMenuManager->StatusMenuPos.y + (20 * (i + 1)) + ((cMenuManager->CharaWindowHeight) * (i));

		i++;
		c->changeWindowPos(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2), c->cWindow->windowPos.y, 1);*/
		//�L�����N�^�[���Ƃ̃E�B���h�E�`��
		c->charaEnhanceWindow->Menu_Draw();

		DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 20, String_Color_Black, "���O:%s", c->charadata->name_.c_str());

		/*�{�^���̍��W�ύX
		c->enhanceButton->menu_x = cMenuManager->StatusMenuPos.x + 150;
		c->enhanceButton->menu_y = c->cWindow->windowPos.y+100;*/


		//�L�����N�^�[�E�B���h�E���Ƃ̃{�^���`��
		c->enhanceButton->Menu_Draw();

		//DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 10, c->cWindow->windowPos.y + 40, String_Color_Black, "������:%s", c->charadata->myTraining.c_str());
		DrawStringEx(c->enhanceButton->menu_x + 10, c->enhanceButton->menu_y + 20, String_Color_Black, "������:%s", c->charadata->myTraining.c_str());


	}
}

void TrainingScene::DrawAbility(Chara* c)
{
	if (c->charadata->Ability.empty() == false) {

		int i = 0;
		for (auto abi : c->charadata->Ability) {

			DrawStringEx(c->cWindow->windowPos.x - (cMenuManager->CharaWindowWidth / 2) + 300, c->cWindow->windowPos.y + 10 + (20 * i),
				String_Color_Black, "%s", abi->ability_name.c_str());
			++i;
		}
	}


}

void TrainingScene::NewCharaWindow()
{
	eventFrame->Menu_Draw();

}

void TrainingScene::ChangeSequence(sequence seq)
{
	nowSeq = seq;
	if (seq == sequence::main) {
		main_sequence_.change(&TrainingScene::Seq_Training_Main);
	}
	else if (seq == sequence::loop) {
		main_sequence_.change(&TrainingScene::Seq_LoopDay);
	}
	else if (seq == sequence::doEvent) {
		main_sequence_.change(&TrainingScene::Seq_DoEvent);
	}
	else if (seq == sequence::eventDraw) {
		main_sequence_.change(&TrainingScene::Seq_EventFrameDraw);
	}
	else if (seq == sequence::newChara) {
		main_sequence_.change(&TrainingScene::Seq_NewCharactorComing);
	}
	else if (seq == sequence::menu_1) {
		main_sequence_.change(&TrainingScene::Seq_MenuDraw_1);
	}
	else if (seq == sequence::menu_2) {
		main_sequence_.change(&TrainingScene::Seq_MenuDraw_2);
	}
	else if (seq == sequence::exit) {
		main_sequence_.change(&TrainingScene::Seq_ExitDay);
	}
	else if (seq == sequence::selectEnhance) {
		main_sequence_.change(&TrainingScene::Seq_SelectEnhance);
	}
	else if (seq == sequence::Set) {
		main_sequence_.change(&TrainingScene::Seq_SetEnhance);
	}

}

void TrainingScene::menuInit()
{
	menu_1 = new Menu(10, 10, 1010, 700, "graphics/WindowBase_02.png");
	chara_1 = new Menu(menu_1->menu_x + 10, menu_1->menu_y + 10, 990, 150, "graphics/WindowBase_01.png");

	yearly = new Menu(chara_1->menu_x + 10, chara_1->menu_y + 85, 55, 60, "graphics/WindowBase_01.png");

	name = new Menu(chara_1->menu_x + 10, chara_1->menu_y + 10, 165, 70, "graphics/WindowBase_01.png");

	stance = new Menu(yearly->menu_x + 55, chara_1->menu_y + 85, 55, 60, "graphics/WindowBase_01.png");

	range = new Menu(yearly->menu_x + 110, chara_1->menu_y + 85, 55, 60, "graphics/WindowBase_01.png");


	//�\�͒l�̖��O�̘g
	menu_3 = new Menu(range->menu_x + 60, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_4 = new Menu(menu_3->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_5 = new Menu(menu_4->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_6 = new Menu(menu_5->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_7 = new Menu(menu_6->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_8 = new Menu(menu_7->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");
	menu_9 = new Menu(menu_8->menu_x + menu_3->menu_width + buff, chara_1->menu_y + 10, width, 50, "graphics/WindowBase_01.png");


	menu_status_1 = new Menu(menu_3->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_2 = new Menu(menu_4->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_3 = new Menu(menu_5->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_4 = new Menu(menu_6->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_5 = new Menu(menu_7->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_6 = new Menu(menu_8->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
	menu_status_7 = new Menu(menu_9->menu_x, chara_1->menu_y + 65, width, 80, "graphics/WindowBase_02.png");
}

