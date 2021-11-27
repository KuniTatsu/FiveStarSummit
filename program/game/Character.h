#pragma once
#include<string>
#include<vector>
class CharaWindow;
class Ability;

class Chara {

public:
	Chara(std::string name);
	~Chara();

	CharaWindow* cWindow;

	typedef struct {
		std::string name_;	//���O
//---------�S�ʃX�e-------------------2
		int RANGETYPE;	//�����W�K�� 0:�Z,1:��,2:��
		int STANCE;		//�퓬�X�^���X 0:���U,1:����,2:����,3:����
//---------��b�X�e-------------------7
		/*class status{
		public:*/
		int ATACK;      //�����U���� 
		int DEFENCE;	//�����h���
		int MAGIATACK;	//���@�U����
		int MAGIDEFENCE;//���@�h���
		int SPEED;		//�f����
		int MIND;		//����
		int VITALITY;	//���v��
	//};

		/*status sta;*/
//---------��b�X�e�o���l-------------------7
		int EXP_ATACK;		//�����U���͌o���l
		int EXP_DEFENCE;	//�����h��͌o���l
		int EXP_MAGIATACK;	//���@�U���͌o���l
		int EXP_MAGIDEFENCE;//���@�h��͌o���l
		int EXP_SPEED;		//�f�����o���l
		int EXP_MIND;		//�����o���l
		int EXP_VITALITY;	//���v�͌o���l

//---------�g���X�e-------------------4
		int CHANCE;		//�`�����X���̋��� 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int PINCH;		//�s���`���̋��� 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int VSINFIGH;	//�΋ߋ����̋��� 0:G,1:F,2:E,3:D,4:C,5:B,6:A
		int VSRANGE;	//�Ή������̋��� 0:G,1:F,2:E,3:D,4:C,5:B,6:A
//---------����\��-------------------1
		std::vector<Ability*> Ability;	//�����A�r���e�B
//---------�e���V����---------------------1
	//����--------------->�ǂ�
		//0...1...2...3...4
		int tension = 2;//default
//---------��������---------------------1
		//int training_ToDo = 0;


	}SaveData_t;
	SaveData_t* charadata = nullptr;

private:
	int StatusRandom(int maxnum, int randomtype);


};