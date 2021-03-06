#pragma once
#include<string>
#include<vector>
class CharaWindow;
class Ability;
class Menu;
class Skill;

class Chara {

public:
	Chara(std::string name, int year);
	~Chara();

	CharaWindow* cWindow;

	enum {
		おまかせ,
		攻撃力,
		防御力,
		魔法攻撃力,
		魔法防御力,
		素早さ,
		賢さ,
		持久力,
		MENU_MAX
	};
	static std::string trainingAll[MENU_MAX];

	//trainingMenu myMenu = trainingMenu::Random;


	typedef struct {
		std::string name_;	//名前
//---------全般ステ-------------------2
		int WEAPON;		//使用武器 0:剣,1:槍,2:杖,3:弓,4:拳　初期はすべて0
		int RANGETYPE;	//レンジ適正 0:短,1:中,2:長
		int STANCE;		//戦闘スタンス 0:速攻,1:堅実,2:反撃,3:普通
//---------基礎ステ-------------------7
		//
		int ATACK;      //物理攻撃力 
		int DEFENCE;	//物理防御力
		int MAGIATACK;	//魔法攻撃力
		int MAGIDEFENCE;//魔法防御力
		int SPEED;		//素早さ
		int MIND;		//賢さ
		int VITALITY;	//持久力
	//};

		/*status sta;*/
//---------基礎ステ経験値-------------------7
		int EXP_ATACK;		//物理攻撃力経験値
		int EXP_DEFENCE;	//物理防御力経験値
		int EXP_MAGIATACK;	//魔法攻撃力経験値
		int EXP_MAGIDEFENCE;//魔法防御力経験値
		int EXP_SPEED;		//素早さ経験値
		int EXP_MIND;		//賢さ経験値
		int EXP_VITALITY;	//持久力経験値

//---------拡張ステ-------------------4
		int CHANCE;		//チャンス時の強さ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int PINCH;		//ピンチ時の強さ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int VSINFIGH;	//対近距離の強さ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int VSRANGE;	//対遠距離の強さ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
//---------特殊能力-------------------1
		std::vector<Ability*> Ability;	//所持アビリティ パッシブ発動
		std::vector<Skill*> Skill;	//所持スキル アクティブ発動
//---------テンション---------------------1
	//悪い--------------->良い
		//0...1...2...3...4
		int tension = 2;//default
//---------強化項目---------------------1
		//int training_ToDo = 0;
		std::string  myTraining = Chara::trainingAll[Chara::おまかせ];
		//---------何年在籍か-------------------1
		int stayYear = 0;
	}SaveData_t;
	SaveData_t* charadata = nullptr;

	//int myGh = 0;
	std::vector<int>gh = {};
	//直近で追加されたアビリティ
	std::string recentAddedAbility = {};

	Menu* charaListWindow = nullptr;

	Menu* charaEnhanceWindow = nullptr;
	Menu* enhanceButton = nullptr;

	//typeが0ならListWindowの座標を変える
	//typeが1ならEnhanceWindowの座標を変える
	void changeWindowPos(int x, int y, int type);

	//void CharaStatusDraw();

	

private:
	int StatusRandom(int maxnum, int randomtype,int year);


};