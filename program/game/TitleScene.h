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




    void Update();  //�O���[�o���}�b�v��ʂł̓���S�ā����܂ō���Ă����@�\�̂��ׂāH

    void Draw();    //���j���[��ʁA�w�i�摜�A�^�C�g�������̕`��

private:

};