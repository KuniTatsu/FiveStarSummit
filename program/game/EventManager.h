#pragma once
#include<list>
#include<vector>
#include<string>

class Event;
class CardEvent;
class ForcedStopDay;
class ExtraEvent;

//�C�x���g���e��ۑ�����N���X
class EventManager {

public:

	EventManager();

	ExtraEvent* exEvent = nullptr;

	std::vector< std::vector<std::string> > event_all;
	//�ǂݍ��񂾃C�x���g���i�[����vector
	std::vector<std::vector<Event*> >eventList;

	//�Q�[�����s���Ɉ�x�����ĂԃC�x���g���[�h�֐�
	void loadEvent();
	//DayCell������邽�тɌĂԃC�x���g�Z�b�g�֐�
	int setEvent(int eventType);

	int setCardEvent(int eventType);


	std::vector< std::vector<std::string> > cardEvent_all;

	std::vector<std::vector<CardEvent*>> cardEventList;

	//�Q�[�����s���Ɉ�x�����ĂԃC�x���g���[�h�֐�
	void loadCardEvent();


	//0���X�e�[�^�X�㏸,�����C�x���g
	//1���X�e�[�^�X�㏸,��邢�C�x���g
	//2���X�e�[�^�X�㏸,�����_���C�x���g
	//3�������X�e�[�^�X�C�x���g(�J�[�h�p)
	void DoEvent(int eventID, int randomnum);
	//������ǉ�����
	//1�����C�p�����[�^up,
	//2������\�͊l��
	//3���A�C�e���l��

	void DoCardEvent(int eventType, int eventId, int PassedDay);
	void loadForcedStopDay();
	std::vector< std::vector<std::string> > ForcedStopDay_All;

	std::vector < ForcedStopDay*> ForcedStopDayList;


	int eventdebugID = 0;
private:
	int Random(int rangeMax);




};