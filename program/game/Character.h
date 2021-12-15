#pragma once
#include<string>
#include<vector>
class CharaWindow;
class Ability;
class Menu;

class Chara {

public:
	Chara(std::string name, int year);
	~Chara();

	CharaWindow* cWindow;

	enum {
		Random,
		ATACK,
		DEFENCE,
		MAGIARACK,
		MAGIDEFENCE,
		SPEED,
		MIND,
		VITALITY,
		MENU_MAX
	};
	static std::string trainingAll[MENU_MAX];

	//trainingMenu myMenu = trainingMenu::Random;


	typedef struct {
		std::string name_;	//ΌO
//---------SΚXe-------------------2
		int RANGETYPE;	//WK³ 0:Z,1:,2:·
		int STANCE;		//ν¬X^X 0:¬U,1:ΐ,2:½,3:Κ
//---------ξbXe-------------------7
		/*class status{
		public:*/
		int ATACK;      //¨UΝ 
		int DEFENCE;	//¨hδΝ
		int MAGIATACK;	//@UΝ
		int MAGIDEFENCE;//@hδΝ
		int SPEED;		//f³
		int MIND;		//«³
		int VITALITY;	//vΝ
	//};

		/*status sta;*/
//---------ξbXeo±l-------------------7
		int EXP_ATACK;		//¨UΝo±l
		int EXP_DEFENCE;	//¨hδΝo±l
		int EXP_MAGIATACK;	//@UΝo±l
		int EXP_MAGIDEFENCE;//@hδΝo±l
		int EXP_SPEED;		//f³o±l
		int EXP_MIND;		//«³o±l
		int EXP_VITALITY;	//vΝo±l

//---------g£Xe-------------------4
		int CHANCE;		//`XΜ­³ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int PINCH;		//s`Μ­³ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int VSINFIGH;	//Ξί£Μ­³ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int VSRANGE;	//Ξ£Μ­³ 0:G,1:F,2:E,3:D,4:C,5:B,6:A
//---------Ακ\Ν-------------------1
		std::vector<Ability*> Ability;	//AreB
//---------eV---------------------1
	//«’--------------->Η’
		//0...1...2...3...4
		int tension = 2;//default
//---------­»Ϊ---------------------1
		//int training_ToDo = 0;
		std::string  myTraining = Chara::trainingAll[Chara::Random];
		//---------½NέΠ©-------------------1
		int stayYear = 0;
	}SaveData_t;
	SaveData_t* charadata = nullptr;

	//int myGh = 0;
	std::vector<int>gh = {};
	std::string recentAddedAbility = {};
	Menu* charaListWindow = nullptr;

	Menu* charaEnhanceWindow = nullptr;
	Menu* enhanceButton = nullptr;
	//typeͺ0ΘηListWindowΜΐWπΟ¦ι
	//typeͺ1ΘηEnhanceWindowΜΐWπΟ¦ι
	void changeWindowPos(int x, int y, int type);


private:
	int StatusRandom(int maxnum, int randomtype);


};