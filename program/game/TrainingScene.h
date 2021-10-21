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

    //新しく一日分のセルを作る関数
    DayCell* createDayCell(int cellnum);

    //一日経過すると一つセルを消去する
    void CellDelete();
  
    //すべてのセルを入れておくリスト
    std::list<DayCell*> cell_;

    //一番左の画像のx座標
    const float mass_x = 50;
    //画像間の距離(画像の大きさは50x50)
    const float mass_width = 70;

    //マス画像を表示するための中心座標
    t2k::Vector3 tbl[7] = {
        {mass_x, 50, 0},
        {mass_x+mass_width*1, 50, 0},
        {mass_x + mass_width * 2, 50, 0},
        {mass_x + mass_width * 3, 50, 0},
        {mass_x + mass_width * 4, 50, 0},
        {mass_x + mass_width * 5, 50, 0},
        {mass_x + mass_width * 6, 50, 0},
    };

    //初期シークエンスを設定
    t2k::Sequence<TrainingScene*> main_sequence_ =
        t2k::Sequence<TrainingScene*>(this, &TrainingScene::Seq_Training_Main);

    TrainingScene();
    ~TrainingScene();

    //メインシークエンス 各処理へ移行する
    bool Seq_Training_Main(const float deltatime);
    //日数経過中のシークエンス ループカウントが0になるまで繰り返す ループカウント:経過日数
    bool Seq_LoopDay(const float deltatime);

    int loopdaycount = 0;
    



    void Update();  

    void Draw();    //メニュー画面、背景画像、タイトル文字の描画

private:
    int time_ = 0;
    int sequenceID=0;
    bool isnowLoop = false;
};