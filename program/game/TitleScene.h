#pragma once
#include"Scene.h"

class Menu;

class TitleScene : public BaseScene {
public:

    Menu* title_back = nullptr;

    TitleScene();
    ~TitleScene();

    int title_gh = 0;
    int enter_gh = 0;

    int title_name_gh = 0;

    int String_Color_Black;

    bool nowFade = false;

    void Update();  

    void Draw();    

private:

};