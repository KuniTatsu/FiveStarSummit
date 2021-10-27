#include "DayCell.h"
#include "DxLib.h"
#include "../library/t2klib.h"
#include "SceneManager.h"
#include "TrainingScene.h"
#include<time.h>


DayCell::DayCell(int cell_gh)
{
	//SRand(time(0));

	if (0 <= cell_gh&&cell_gh<=5) {
		//0�͐}�X �v���X���ʂ̃C�x���g����������
		gh = LoadGraph("graphics/blue.png");
	}
	else if (6 <= cell_gh&& cell_gh <=8) {
		//1�͐ԃ}�X �}�C�i�X���ʂ̃C�x���g����������
		gh = LoadGraph("graphics/red.png");
	}
	else if (9 <= cell_gh&& cell_gh<=15) {
		//2�͔��}�X �v���X���ʂƃ}�C�i�X���ʂ������_���őI�΂��
		//�o�����4~10���̓v���X��7��,11��~3���̓}�C�i�X��7�����炢�ɕ΂点����
		gh = LoadGraph("graphics/white.png");
	}


	//gh = cell_gh;
	//tScene->cell_.emplace_back(this);
	//SceneManager::m_pScene
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
	//DrawGraph(pos_.x, pos_.y, gh, false);
}
