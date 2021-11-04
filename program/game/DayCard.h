#pragma once
#include"../library/t2klib.h"


class DayCard {

public:

	DayCard(int randomNum);
	~DayCard();

	//�J�[�h�̉�ʓ��̈ʒu
	t2k::Vector3 pos_;

	//�J�[�h�̑傫��
	const int CardWidth = 100;
	const int CardHeight = 120;

	double exRate = 1;

	unsigned int Color = 0;

	//�J�[�h�̒��̐����̏ꏊ�����߂�vector
	const t2k::Vector3 initpos = { -40, -50, 0 };

	//�o�ߓ���
	int passedDayNum = 0;

	//�J�[�h���g�����Ƃ��ɋN����C�x���g��id
	int cardEventId = 0;

	//�J�[�h�����t���O
	bool isLive = true;
	//�I�΂ꂽ�t���O
	bool isSelected = false;

	void Update();
	void Draw();

private:

	//�O���t�B�b�N�n���h��
	int gh = 0;


};