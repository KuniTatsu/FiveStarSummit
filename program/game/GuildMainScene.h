#pragma once
#include"Scene.h"


class Player;


class GuildMainScene : public BaseScene {
public:

    bool changeSceneFlag;
    int encountrand = 0;

    GuildMainScene();
    ~GuildMainScene();

    Player* player = nullptr;
    



    void Update();  //�O���[�o���}�b�v��ʂł̓���S�ā����܂ō���Ă����@�\�̂��ׂāH

    void Draw();    //���j���[��ʁA�w�i�摜�A�^�C�g�������̕`��

private:

};