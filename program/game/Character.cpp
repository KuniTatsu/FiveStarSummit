#include "Character.h"
//
//
//playerdata = new SaveData_t;
//*playerdata = { "�v���C���[",100.0f,100.0f , 10/*1000*/,10, 0,0, 1,1,0,0,0 };

Chara::Chara()
{

	charadata = new SaveData_t;

	//���ۂ͐������Ƀ����_���Œl�����߂�
	*charadata = { "�ق��ق�",
					0,0,
					10,20,30,40,50,60,70,
					 0, 0, 0, 0, 0, 0, 0,
					0,0,0,0,
					{} ,
					2};

}

Chara::~Chara()
{



}
