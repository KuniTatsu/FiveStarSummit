#pragma once

class FadeControl {

public:

	FadeControl();

	//�摜�����X�ɕ\������֐�
	void imageFadeIn(int x, int y, double rate, int gh);

	//�摜�����X�ɏ����֐�
	void imageFadeOut();

private:

	int imageFade = 0;
	const int FADESPEED = 5;





};