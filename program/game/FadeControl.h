#pragma once

class FadeControl {

public:

	FadeControl();

	//画像を徐々に表示する関数
	void imageFadeIn(int x, int y, double rate, int gh);

	//画像を徐々に消す関数
	void imageFadeOut();

private:

	int imageFade = 0;
	const int FADESPEED = 5;





};