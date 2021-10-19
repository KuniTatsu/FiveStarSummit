#pragma once
#include"Scene.h"
#include<list>
#include"../library/t2klib.h"

class DayCell;
class EventManager;

class TrainingScene : public BaseScene {
public:
    EventManager* eManager = nullptr;


    bool changeSceneFlag=false;

    DayCell* createDayCell(int cellnum);

    void CellDelete();
  
    std::list<DayCell*> cell_;

    //��ԍ��̉摜��x���W
    const float mass_x = 50;
    //�摜�Ԃ̋���(�摜�̑傫����50x50)
    const float mass_width = 70;

    //�}�X�摜��\�����邽�߂̒��S���W
    t2k::Vector3 tbl[7] = {
        {mass_x, 50, 0},
        {mass_x+mass_width*1, 50, 0},
        {mass_x + mass_width * 2, 50, 0},
        {mass_x + mass_width * 3, 50, 0},
        {mass_x + mass_width * 4, 50, 0},
        {mass_x + mass_width * 5, 50, 0},
        {mass_x + mass_width * 6, 50, 0},

        /*{30, 50, 0},
        {100, 50, 0},
        {170, 50, 0},
        {240, 50, 0},
        {310, 50, 0},
        {380, 50, 0},
        {450, 50, 0},*/

    };

    t2k::Sequence<TrainingScene*> main_sequence_ =
        t2k::Sequence<TrainingScene*>(this, &TrainingScene::Seq_Training_Main);

    TrainingScene();
    ~TrainingScene();

    bool Seq_Training_Main(const float deltatime);
    bool Seq_LoopDay(const float deltatime);

    int loopdaycount = 0;




    void Update();  

    void Draw();    //���j���[��ʁA�w�i�摜�A�^�C�g�������̕`��

private:

};