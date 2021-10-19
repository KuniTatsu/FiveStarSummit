#pragma once
#include<vector>
class SceneManager;
class Character;

class GameManager {

public:

	GameManager();
	~GameManager();

	SceneManager* sManager = nullptr;

	std::vector<Character> chara = {};

	void MakeCharacter();

	void StatusSet(int setType);

	void Update();
	void Draw();


};