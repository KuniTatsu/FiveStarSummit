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
#include"DayCard.h"

extern GameManager* gManager;


TrainingScene::TrainingScene()
{
	eManager = new EventManager();

	SRand(time(0));

	LoadDivGraph("graphics/player_chara_act_right.png", 4, 4, 1, 32, 32, playergh, false);

	//�ŏ���7���X�g�ɓ���鏈��������
	for (int k = 0; k < 7; ++k) {
		int random = GetRand(15);
		createDayCell(random);
	}
	for (int k = 0; k < 5; ++k) {
		createDayCard();
	}
}

TrainingScene::~TrainingScene()
{
}

//�����J�[�h���I�΂��܂ł̃V�[�N�G���X(�����ړ��ς�)
bool TrainingScene::Seq_Training_Main(const float deltatime)
{
	//loopdaycount��0�łȂ���΃V�[�N�G���X��LoopDay�ɂ���
	//loopdaycount��0�ɂȂ�����cell_���X�g��3�Ԗڂ̃C�x���g��ǂݍ���	

	if (main_sequence_.isStart()) {
		sequenceID = 0;
	}

#if 0
	if (isnowLoop == false) {
		DrawStringEx(200, 500, -1, "��������͂��Ă�");
		std::cin >> loopdaycount;

		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
			main_sequence_.change(&TrainingScene::Seq_LoopDay);
			isnowLoop = true;
		}
	}

#endif

	//���[�v���������肷�鏊
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN) && isnowLoop == false) {
		isnowLoop = true;
		doneFirstEvent = true;
		doneEvent = false;

		//*********Debug******************//
		//�o�߂�����������o��
		//loopdaycount = GetRand(4) + 1;//�ꎞ�I��1~5���̊ԂŌo�ߓ��������܂�悤�ɐݒ�
		//*********************************//

		//���ݑI�𒆂̃J�[�h�̌o�ߓ�����ǂݍ���
		//loopdaycount�ɑ��
		int c = 0;
		for (auto card : card_) {
			if (c == selectNum) {
				loopdaycount = card->passedDayNum;
			}
			
			c++;
		}

		addLog(std::to_string(loopdaycount) + "���o�߂����");

		//�J�[�h�������オ��A�g�債�Ĉ��ȏ�̑傫���ɂȂ�Ə�����V�[�N�G���X���͂��݂���
		main_sequence_.change(&TrainingScene::Seq_LoopDay);
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
			main_sequence_.change(&TrainingScene::Seq_LoopDay);

		}
	}
	else {
		if (doneFirstEvent == false)return true;
		std::list<DayCell*>::iterator it = cell_.begin();
		//it += 2;�@�ł��Ȃ�
		++it;
		++it;//iterator��3�ԖڂɈړ�
		//�C�x���gID���擾
		//�l���邱��:�ǂ��Ŏ��ۂɎ��s�����C�x���g�����肷�邩
			// ��1:new�����Ƃ���cell�̐F�ɂ���ăC�x���g���X�g�����܂�A�����_���ŃC�x���g���ݒ肳���
			//   2:loopdaycount��0�ɂȂ����Ƃ��ɐF���擾���ăC�x���g���X�g�����߁A�����_���ŃC�x���g��ݒ肷��

		int event = (*it)->eventID;

		if (doneEvent == false) {
			//eventID��0,1,2
			int size = eManager->eventList[event].size();
			int rand = GetRand(size - 1);
			eManager->DoEvent(event, rand);

			//�N�����C�x���g�̓��e�����O�ŏo�͂�����

			if (eManager->eventList[event][rand]->num_ > 0) {
				addLog(eManager->eventList[event][rand]->StatusName_ + "��" + std::to_string(eManager->eventList[event][rand]->num_) + "��������");
			}
			else {
				int hoge = eManager->eventList[event][rand]->num_ * (-1);
				addLog(eManager->eventList[event][rand]->StatusName_ + "��" + std::to_string(hoge) + "��������");
			}
			doneEvent = true;
		}

		isnowLoop = false;
	}
	return true;
}

bool TrainingScene::Seq_CardDisappear(const float deltatime)
{
	//�J�[�h��傫������

	main_sequence_.change(&TrainingScene::Seq_LoopDay);
	return true;
}

//�����J�[�h���I�΂ꂽ���Ƃ̃V�[�N�G���X(�����ړ�)
bool TrainingScene::Seq_LoopDay(const float deltatime)
{

	if (main_sequence_.isStart()) {
		sequenceID = 1;
	}
	//������DayCell��ǉ�������������肷�鏈��������
	//�V����1��DayCell�����
	int random = GetRand(15);
	createDayCell(random);
	//DayCell* p = new DayCell(0);
	//���X�g��1�Ԃ����X�g����O����delete���鐶��
	CellDelete();
	loopdaycount--;
	main_sequence_.change(&TrainingScene::Seq_Training_Main);
	return true;
}

DayCell* TrainingScene::createDayCell(int cellnum) {

	//cellnum:0����,1����,2����
	DayCell* new_obj = new DayCell(cellnum);

	//DayCell���̂�eventID�����肷��

	new_obj->eventID = eManager->setEvent(cellnum);

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

DayCard* TrainingScene::createDayCard()
{
	DayCard* new_card = new DayCard();
	int daynum = GetRand(4) + 1;
	new_card->passedDayNum = daynum;
	new_card->pos_.y = 620;

	card_.emplace_back(new_card);

	return new_card;
}


//�V�[�N�G���X�Ɉˑ����Ȃ��V�[�����̑S�ʏ����������ōs��
void TrainingScene::Update()
{
	main_sequence_.update(gManager->deitatime_);


	//�b��I�ȃL�����쐬
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE)) {

		gManager->MakeCharacter();
		//�o�͗��Ƀ��b�Z�[�W�o�������񂾂��Ǐo�Ȃ��񂾂��ǁI
		//std::cout << "�L�������쐬����܂���" << std::endl;
		t2k::debugTrace("\n�L�������쐬����܂���\n");
	}

	//--------------debugend------------------------//

	for (auto hoge : cell_) {
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
	cardSelect();

	//------debug------
	int k = 0;
	for (auto c : cell_) {

		DrawStringEx(50, 400 + k * 50, -1, "%d", c->eventID);
		++k;
	}
	DrawStringEx(100, 300, -1, "%d", loopdaycount);
	//if(main_sequence_==&TrainingScene::Seq_Training_Main)
	//���݂̃V�[�N�G���X��if���ŕ]��������
	if (sequenceID == 0) {
		DrawStringEx(100, 350, -1, "SeqTrainingMain");
	}
	else {
		DrawStringEx(100, 350, -1, "SeqLoopDay");
	}

	DrawStringEx(100, 400, -1, "�C�x���gID��%d", eManager->eventdebugID);

	DrawRotaGraph(190, 50, 1, 0, playergh[2], true);
	//--------------------

	LogDraw();
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




