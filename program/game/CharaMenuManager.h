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

	//ステータス画面の座標(これを動かすと他のステータスの枠が全部動く)
	t2k::Vector3 StatusMenuPos = { 512,50,0 };

	////キャラ一人一人の枠の座標::ステータス画面の座標からの相対座標
	t2k::Vector3 CharaWakuPos = {};
	////ステータスの表示座標::枠の座標からの相対座標

	//上の２つは描画するときに計算する

	CharaMenuManager();
	~CharaMenuManager();

	void DrawWindow();

	void AddList(CharaWindow* cWindow);
private:

};

