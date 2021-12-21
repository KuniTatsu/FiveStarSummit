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

		//// ********** フォントのロード **********
		//LPCSTR font_path = "DragonQuestFC.ttf"; // 読み込むフォントファイルのパス
		//if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		//}
		//else {
		//	// フォント読込エラー処理
		//	MessageBox(NULL, "フォント読込失敗", "", MB_OK);
		//}

		init = true;
	}


	gManager->deitatime_ = deltatime;
	gManager->Update();
	gManager->Draw();


}



