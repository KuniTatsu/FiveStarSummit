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

    //�V����������̃Z�������֐�
    DayCell* createDayCell(int cellnum);

    //����o�߂���ƈ�Z������������
    void CellDelete();
  
    //���ׂẴZ�������Ă������X�g
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
    };

    //�����V�[�N�G���X��ݒ�
    t2k::Sequence<TrainingScene*> main_sequence_ =
        t2k::Sequence<TrainingScene*>(this, &TrainingScene::Seq_Training_Main);

    TrainingScene();
    ~TrainingScene();

    //���C���V�[�N�G���X �e�����ֈڍs����
    bool Seq_Training_Main(const float deltatime);
    //�����o�ߒ��̃V�[�N�G���X ���[�v�J�E���g��0�ɂȂ�܂ŌJ��Ԃ� ���[�v�J�E���g:�o�ߓ���
    bool Seq_LoopDay(const float deltatime);

    int loopdaycount = 0;




    void Update();  

    void Draw();    //���j���[��ʁA�w�i�摜�A�^�C�g�������̕`��

private:
    int time_ = 0;
};