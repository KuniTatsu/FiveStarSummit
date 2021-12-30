#include "TitleScene.h"
#include"GameManager.h"
#include"DxLib.h"
#include "../library/t2klib.h"
#include "../support/Support.h"
#include"SceneManager.h"
#include"MenuWindow.h"
#include"FadeControl.h"
#include"SoundManager.h"


extern GameManager* gManager;

TitleScene::TitleScene()
{
	gManager->sound->BGM_Play(gManager->sound->bgm_title);
	String_Color_Black = GetColor(0, 0, 0);

	title_gh = gManager->LoadGraphEx("graphics/sougenna.jpg");
	enter_gh = gManager->LoadGraphEx("graphics/button_Enter.png");
	title_name_gh = gManager->LoadGraphEx("graphics/Title.png");

	title_back = new Menu(384, 334, 250, 80, "graphics/WindowBase_02.png");
}

TitleScene::~TitleScene()
{
	StopSoundMem(gManager->sound->bgm_title);
}

void TitleScene::Update()
{
	
	

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {

		gManager->sound->System_Play(gManager->sound->system_select);
		nowFade = true;
		/*SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);
		return;*/
	}
	if (nowFade) {
		gManager->fControl->FadeOut();
	}
	if (gManager->fControl->doneFade != true)return;
	SceneManager::ChangeScene(SceneManager::SCENE::TRAINING);
	return;
	//ゲームの開始処理
	//TrainingSceneへ飛ばす

	//なにかキーボードを押したらorボタンを押したらゲームが終了する
	//終了する前に以下の情報を外部ファイルに保存する
	//現在の在籍キャラクターのステータス
	//日にちの進捗状況
	//所持しているカードの日にちとイベント
	//Daycellのイベントidとgh


}

void TitleScene::Draw()
{
	
	DrawRotaGraph(512, 384, 1.28, 0, title_gh, true);

	DrawRotaGraph(512, 100, 1, 0, title_name_gh, true);

	title_back->Menu_Draw();
	DrawRotaGraph(512, 364, 1, 0, enter_gh, true);
	DrawStringEx(400, 380, String_Color_Black, "Enterを押してゲームスタート");




	//タイトル画像の描画
	//タイトルメニューの描画
}
