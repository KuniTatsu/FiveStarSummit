#pragma once
#include<string>

class CardEvent {

public:
	CardEvent(int ID, int Eventtype, int Statustype, int num, std::string desc, std::string StatusName,
		int ID2, int Eventtype2, int Statustype2, int num2, std::string desc2, std::string StatusName2);
	~CardEvent();

	

	//eventID
	int id_ = 0;
	//0,1,2...master�Q��
	int event_type_ = 0;
	//�ω�����X�e�[�^�X
	int status_type_ = 0;
	//�ω���
	int num_ = 0;
	//����
	std::string desc_ = {};
	//�ω�����X�e�[�^�X�̖��O
	std::string StatusName_;

	//******�J�[�h�p�X�e�[�^�X*****//
	//�Q�ڂ̕ω�����X�e�[�^�X
	int event_type_second_ = 0;
	int status_type_second_ = 0;
	int num_second_ = 0;
	//����
	std::string desc__second_ = {};
	//�ω�����X�e�[�^�X�̖��O
	std::string StatusName_second_;

	void run_Card_Event();

};