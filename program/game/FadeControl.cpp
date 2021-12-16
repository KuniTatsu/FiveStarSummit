#include "FadeControl.h"
#include"DxLib.h"
#include"GameManager.h"

extern GameManager* gManager;

FadeControl::FadeControl()
{
}

void FadeControl::imageFadeIn(int x, int y, double rate, int gh)
{

	if (imageFade >= 0 && imageFade < 256) {                   //cが0~256の時
		//SetDrawBright(imageFade, imageFade, imageFade);        //段々あかるく(c= 0->255)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, imageFade);		//だんだん画像を鮮明に

		DrawRotaGraph(x, y, rate, 0, gh, true);

		imageFade += FADESPEED;//imageFadeをカウントアップ


	}
	else {
		//設定を元に戻す。

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		return;
	}


}

void FadeControl::imageFadeOut()
{



}
