#pragma once

class FadeControl {

public:

	FadeControl();

	//画像を徐々に表示する関数
	void imageFadeIn(int x, int y, double rate, int gh);

	//画像を徐々に消す関数
	void imageFadeOut();


	//画面を徐々に消す関数
	void FadeOut();
	//画面を徐々に出す関数
	void FadeIn();

	bool doneFade = false;

private:

	int imageFade = 0;
	const int FADESPEED = 5;

	int screenFade = 256;






};