#include "DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include "game_main.h"
#include"GameManager.h"


GameManager* gManager = nullptr;


bool init = false;

void gameMain( float deltatime ) {

	if (!init) {

		gManager = new GameManager();

		init = true;
	}
	

	gManager->deitatime_ = deltatime;
	gManager->Update();
	gManager->Draw();

	
}



