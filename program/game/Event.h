#pragma once
#include<string>

class Event {

public:
	Event(int ID, int Eventtype, int Statustype, int num, std::string desc,std::string StatusName,std::string EventName,std::string EventMessage);
	~Event();

	

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
	std::string statusName="" ;
	//�C�x���g��
	std::string eventName = "";;
	//�C�x���g���b�Z�[�W
	std::string eventMessage = "";
	


	void run_Status_Event();

};