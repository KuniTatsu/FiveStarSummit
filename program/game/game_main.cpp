#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_main.h"
#include"GameManager.h"


GameManager* gManager = nullptr;


bool init = false;

void gameMain(float deltatime) {

	if (!init) {

		gManager = new GameManager();

		gManager->initGameManager();

		//// ********** �t�H���g�̃��[�h **********
		//LPCSTR font_path = "DragonQuestFC.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
		//if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		//}
		//else {
		//	// �t�H���g�Ǎ��G���[����
		//	MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
		//}

		init = true;
	}


	gManager->deitatime_ = deltatime;
	gManager->Update();
	gManager->Draw();


}



