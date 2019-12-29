#pragma once
#include "gameNode.h"
#include "player.h"

class playerEric : public player
{
private:
	tagPlayer _eric;
	RECT _test;
	bool _ericAttack;
	bool _ericJump;
	bool _ericUnable;		// 전투 불능 상태
	bool _isHit;
	bool _isBreath;
	int _hitCount;
	int _breathCount;
	int _breathFrameCount;
	float _jumpStart;

public:
	playerEric();
	~playerEric();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();
	virtual void key();

	void frameCount();
	void ericJump();
	void ericAttack();
	void ericAttackMove();
	void setEricImage();

	tagPlayer getEric() { return _eric; }
	void setEricX(float x) { _eric.x = x; }	 // eric x 설정
	void setEricY(float y) { _eric.y = y; }  // eric y 설정 

	float getEricProbeX() { return _eric.probeX; }
	float getEricProbeY() { return _eric.probeY; }
};

