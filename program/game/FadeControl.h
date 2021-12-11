#pragma once

class FadeControl {

public:

	FadeControl();

	//‰æ‘œ‚ğ™X‚É•\¦‚·‚éŠÖ”
	void imageFadeIn(int x, int y, double rate, int gh);

	//‰æ‘œ‚ğ™X‚ÉÁ‚·ŠÖ”
	void imageFadeOut();

private:

	int imageFade = 0;
	const int FADESPEED = 5;





};