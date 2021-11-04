#pragma once
#include"Scene.h"

class BattleScene : public BaseScene {
public:

	bool changeSceneFlag = false;
	int encountrand = 0;

	BattleScene();
	~BattleScene();



	void Update();

	void Draw();

private:

};