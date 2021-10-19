#pragma once
#include"Scene.h"


class Player;


class TitleScene : public BaseScene {
public:

    bool changeSceneFlag=false;
    int encountrand = 0;

    TitleScene();
    ~TitleScene();

    Player* player = nullptr;




    void Update();  //グローバルマップ画面での動作全て→今まで作ってきた機能のすべて？

    void Draw();    //メニュー画面、背景画像、タイトル文字の描画

private:

};