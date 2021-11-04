#include "DayCard.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include"../support/Support.h"

DayCard::DayCard(int randomNum)
{

	gh = LoadGraph("graphics/dayCard.png");
	Color = GetColor(255, 0, 0);
}

DayCard::~DayCard()
{
}

void DayCard::Update()
{

}

void DayCard::Draw()
{
	//�s���J�[�h���w�薇�������ׂĕ\������

	//�I��(�J�[�\���������Ă���)�̍s���J�[�h�̘g���n�C���C�g����
	//�o����Γ_�ł�������
	//�I�𒆂̍s���J�[�h��y���W�𑼂���������Ɉړ�������

	//�ʏ�̃J�[�h�\��
	DrawRotaGraph(pos_.x, pos_.y, exRate, 0, gh, false);
	
	DrawStringEx(pos_.x + initpos.x, pos_.y + initpos.y, Color, "%d", passedDayNum);
	
}
