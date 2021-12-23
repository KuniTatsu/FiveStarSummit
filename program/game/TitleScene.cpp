#include "TitleScene.h"
#include"GameManager.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include"SceneManager.h"


extern GameManager* gManager;

TitleScene::TitleScene()
{
	title_gh = gManager->LoadGraphEx("graphics/sougenna.jpg");
	
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);
		return;
	}
	//�Q�[���̊J�n����
	//TrainingScene�֔�΂�

	//�Ȃɂ��L�[�{�[�h����������or�{�^������������Q�[�����I������
	//�I������O�Ɉȉ��̏����O���t�@�C���ɕۑ�����
	//���݂̍ݐЃL�����N�^�[�̃X�e�[�^�X
	//���ɂ��̐i����
	//�������Ă���J�[�h�̓��ɂ��ƃC�x���g
	//Daycell�̃C�x���gid��gh


}

void TitleScene::Draw()
{
	DrawRotaGraph(512, 384, 1.28, 0, title_gh, true);
	//�^�C�g���摜�̕`��
	//�^�C�g�����j���[�̕`��
}
