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
	bool _isSlide;
	bool _isSlideOn;
	int _hitCount;
	int _breathCount;
	int _breathFrameCount;
	int _slideCount; // 슬라이딩 카운트 
	float _jumpStart;
	float _gravity;
	float _slidePower;

	bool	   _stopControl;		// 이값이 true라면 움직일 수 없다.

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

	void PixelCollision();
	void PixelRightCollision(); // X축 충돌 처리 
	void PixelLeftCollision(); // X축 충돌 처리 
	void isJumpPixelCollision();
	void PixelAirCollision();
	tagPlayer getEric() { return _eric; }

	void setEricX(float x) { _eric.x = x; }	 // eric x 설정
	void setEricY(float y) { _eric.y = y; }  // eric y 설정 

	float getEricProbeX() { return _eric.probeX; }
	float getEricProbeY() { return _eric.probeY; }

	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _eric.isDead = true; }
};

