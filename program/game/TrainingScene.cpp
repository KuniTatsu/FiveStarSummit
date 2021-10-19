#include "TrainingScene.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "DayCell.h"
#include<time.h>
#include"EventManager.h"
#include <iostream>
#include"GameManager.h"

extern GameManager* gManager;


TrainingScene::TrainingScene()
{
	eManager = new EventManager();

	SRand(time(0));

	//�ŏ���7���X�g�ɓ���鏈��������
	for (int k = 0; k < 7; ++k) {
		int random = GetRand(2);
		createDayCell(random);
	}
}

TrainingScene::~TrainingScene()
{
}

//�����J�[�h���I�΂��܂ł̃V�[�N�G���X(�����ړ��ς�)
bool TrainingScene::Seq_Training_Main(const float deltatime)
{
	//loopdaycount��0�łȂ���΃V�[�N�G���X��LoopDay�ɂ���
	//loopdaycount��0�ɂȂ�����cell_���X�g��3�Ԗڂ̃C�x���g��ǂݍ���	todo :DayCell�ɃC�x���gid����������,�C�x���gid��ǂ�Ŏ��s����֐������
	//	��3�ԖڂɃv���C���[����ɒu������

	if (loopdaycount != 0) {
		main_sequence_.change(&TrainingScene::Seq_Training_Main);
	}
	else {

		std::list<DayCell*>::iterator it = cell_.begin();
		//it += 2;�@�ł��Ȃ�
		++it;
		++it;//iterator��3�ԖڂɈړ�
		//�C�x���gID���擾
		//�l���邱��:�ǂ��Ŏ��ۂɎ��s�����C�x���g�����肷�邩
			// ��1:new�����Ƃ���cell�̐F�ɂ���ăC�x���g���X�g�����܂�A�����_���ŃC�x���g���ݒ肳���
			//   2:loopdaycount��0�ɂȂ����Ƃ��ɐF���擾���ăC�x���g���X�g�����߁A�����_���ŃC�x���g��ݒ肷��

		int event = (*it)->eventID;
		//�C�x���g���s�֐�->�ǂ��ɒu�����l����
		// DoEvent(event);
	}


	return true;
}

//�����J�[�h���I�΂ꂽ���Ƃ̃V�[�N�G���X(�����ړ�)
bool TrainingScene::Seq_LoopDay(const float deltatime)
{
	//������DayCell��ǉ�������������肷�鏈��������


	return true;
}

DayCell* TrainingScene::createDayCell(int cellnum) {

	//cellnum:0����,1����,2����
	DayCell* new_obj = new DayCell(cellnum);

	int eventType = 0;

	if (cellnum == 0) {
		eventType = GetRand(3);
	}
	else if (cellnum == 1) {
		eventType = GetRand(3) + 4;
	}
	else if (cellnum == 2) {
		eventType = GetRand(3) + 8;
	}

	//eManager->setEvent(eventType);

	//DayCell���̂�eventID�����肷��
	new_obj->eventID = eManager->setEvent(eventType);

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



void TrainingScene::Update()
{
	//�{���̓J�[�h��I��->�J�[�h�̐i�s���������܂�->�ϐ��ɑ��->�V�[�P���X�ϐ���0�ɂȂ�܂Ŏ~�܂�V�[�P���X�������V�[�P���X���~�܂�V�[�P���X���J��Ԃ�
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		//�V����1��DayCell�����
		int random = GetRand(2);
		createDayCell(random);
		//DayCell* p = new DayCell(0);
		//���X�g��1�Ԃ����X�g����O����delete���鐶��
		CellDelete();
	}

	//�b��I�ȃL�����쐬
	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE)) {

		gManager->MakeCharacter();
		std::cout << "�L�������쐬����܂���" << std::endl;
	}


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
	//------debug------
	for (auto c : cell_) {
		int i = 0;
		DrawStringEx(100, 400 + i * 50, -1, "%d", c->eventID);
	}


}
