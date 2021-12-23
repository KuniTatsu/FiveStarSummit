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
	//タイトル画像の描画
	//タイトルメニューの描画
}
