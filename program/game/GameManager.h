#pragma once
#include<vector>
class SceneManager;
class Chara;

class GameManager {

public:

	GameManager();
	~GameManager();

	SceneManager* sManager = nullptr;
	Chara* chara_ = nullptr;

	std::vector<Chara*> chara = {};

	void MakeCharacter();

	//Xe[^XΟ»Φ
	//setType¨ΗΜXe[^Xπγ°ι©
	//valueEx¨Xe[^XγΈW 1¨{(+10*1),2¨{(+10*2),3¨3{(+10*3)
	void StatusSet(int setType,int valueEx);

	void Update();
	void Draw();


};