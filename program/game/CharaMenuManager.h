#pragma once
#include"DxLib.h"
#include"../library/t2klib.h"
#include"../support/Support.h"
class CharaWindow;

class CharaMenuManager {

public:
	const int CharaWindowWidth = 600;
	const int CharaWindowHeight = 250;

	const int WindowPadding = 20;

	std::list<CharaWindow*> charaWindow_;

	//�X�e�[�^�X��ʂ̍��W(����𓮂����Ƒ��̃X�e�[�^�X�̘g���S������)
	t2k::Vector3 StatusMenuPos = { 512,45,0 };

	////�L������l��l�̘g�̍��W::�X�e�[�^�X��ʂ̍��W����̑��΍��W
	t2k::Vector3 CharaWakuPos = {};
	////�X�e�[�^�X�̕\�����W::�g�̍��W����̑��΍��W

	//��̂Q�͕`�悷��Ƃ��Ɍv�Z����

	CharaMenuManager();
	~CharaMenuManager();

	
	void PosReset();

	void AddList(CharaWindow* cWindow);
private:

};

