#pragma once
#include "gameNode.h"
#include "player.h"
#include <vector>
#define PI 3.141592654



enum ARROWSTATE
{
	SHOT,
	FIRE_SHOT
};
struct tagArrow
{
	image* arrowImage;
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	bool isFire;
	int count;
	int direction;
};

//enum tagBaleogState			// �̹����� ���°�  
//{
//	BALEOG_IDLE_R,
//	BALEOG_IDLE_L,
//	BALEOG_MOVE_R,
//	BALEOG_MOVE_L,
//	BALEOG_ARROW_READY,	   // ���α� ȭ��	
//	BALEOG_ARROW_FIRE,
//	BALEOG_SWORD1,	   // ���α� Į
//	BALEOG_SWORD2,
//	BALEOG_DIE_R,		    // �⺻���� (ü�´޾�����)
//	BALEOG_DIE_L,
//	BALEOG_POISON_R,		// ����
//	BALEOG_POISON_L,
//	BALEOG_MIRRA_R,		// �̶��
//	BALEOG_MIRRA_L,
//	BALEOG_PRESSDIE_R,		// �����
//	BALEOG_PRESSDIE_L,
//	STATE_TRAPDIE_R,		// �Կ� ��� �״»�
//	STATE_TRAPDIE_L
//
//};
class arrow : public gameNode
{
private:
	vector<tagArrow> _vArrow;
	vector<tagArrow>::iterator _viArrow;
	float _range;
	int _arrowMax;
	int _direction;
	ARROWSTATE _arrowState;

public:
	arrow() {};
	~arrow() {};
	virtual HRESULT init(int arrowMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float speed , float angle, int direction);

	void removeArrow(int arrNum);

	void arrowMove(bool fire);

	vector<tagArrow> getVArrow() { return _vArrow; }
	vector<tagArrow>::iterator getViArrow() { return _viArrow; }


};

class playerbaleog : public player
{

private:
	tagPlayer _baleog;
	bool _baleogAttack;
	bool _baleogAttackMotion;
	bool _baleogArrowMotion;
	bool _baleogArrowAction;

	int _baleogAttackCount;

	arrow* _ar;

	bool ss;

public:
	playerbaleog();
	~playerbaleog();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void key();
	void setBaleogState();


	tagPlayer getBaleog() { return _baleog; }
};



