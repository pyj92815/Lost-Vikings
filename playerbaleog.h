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

//enum tagBaleogState			// 이미지의 상태값  
//{
//	BALEOG_IDLE_R,
//	BALEOG_IDLE_L,
//	BALEOG_MOVE_R,
//	BALEOG_MOVE_L,
//	BALEOG_ARROW_READY,	   // 벨로그 화살	
//	BALEOG_ARROW_FIRE,
//	BALEOG_SWORD1,	   // 벨로그 칼
//	BALEOG_SWORD2,
//	BALEOG_DIE_R,		    // 기본죽음 (체력달았을때)
//	BALEOG_DIE_L,
//	BALEOG_POISON_R,		// 독사
//	BALEOG_POISON_L,
//	BALEOG_MIRRA_R,		// 미라사
//	BALEOG_MIRRA_L,
//	BALEOG_PRESSDIE_R,		// 압축사
//	BALEOG_PRESSDIE_L,
//	STATE_TRAPDIE_R,		// 뿔에 찔려 죽는사
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



