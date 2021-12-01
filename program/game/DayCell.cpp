#include "DayCell.h"
#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "SceneManager.h"
#include "TrainingScene.h"
#include<time.h>
#include"GameManager.h"


extern GameManager* gManager;

DayCell::DayCell(int cell_gh)
{
	//SRand(time(0));

	if (0 <= cell_gh && cell_gh <= 5) {
		//0�͐}�X �v���X���ʂ̃C�x���g����������
		gh = gManager->LoadGraphEx("graphics/red.png");

	}
	else if (6 <= cell_gh && cell_gh <= 8) {
		//1�͐ԃ}�X �}�C�i�X���ʂ̃C�x���g����������
		gh = gManager->LoadGraphEx("graphics/blue.png");
	}
	else if (9 <= cell_gh && cell_gh <= 14) {
		//2�͔��}�X �v���X���ʂƃ}�C�i�X���ʂ������_���őI�΂��
		//�o�����4~10���̓v���X��7��,11��~3���̓}�C�i�X��7�����炢�ɕ΂点����
		gh = gManager->LoadGraphEx("graphics/white.png");
	}
	else if (cell_gh == 15) {
		//�X�L���l���}�X �m���ŃX�L�����l���ł���@���X�g����I�ԁ@���������\�������
		gh = gManager->LoadGraphEx("graphics/gold.png");
	}
	else if (cell_gh == 16) {
		gh = gManager->LoadGraphEx("graphics/extraDay_1.png");
	}


	//gh = cell_gh;
	//tScene->cell_.emplace_back(this);
	//SceneManager::m_pScene
	/*dayCell_gh[0] = LoadGraph("graphics/blue.png");
	dayCell_gh[1] = LoadGraph("graphics/red.png");
	dayCell_gh[2] = LoadGraph("graphics/white.png");
	dayCell_gh[3] = LoadGraph("graphics/gold.png");*/
}

DayCell::~DayCell()
{

}

void DayCell::Update()
{
}

void DayCell::Draw()
{
	//	DrawGraph()
	DrawRotaGraph(pos_.x, pos_.y, 1, 0, gh, false);
	DrawStringEx(pos_.x, pos_.y - 40, -1, "%s", myDayName.c_str());
	DrawStringEx(pos_.x-40, pos_.y + 40, -1, "%s", myMonthName.c_str());
	DrawStringEx(pos_.x+10, pos_.y + 40, -1, "%d��", myDay);

	//DrawGraph(pos_.x, pos_.y, gh, false);
}


