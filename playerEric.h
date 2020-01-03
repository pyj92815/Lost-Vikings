#pragma once
#include "gameNode.h"
#include "player.h"

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

class playerEric : public player
{
private:
	tagPlayer _eric;
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

	bool  _stopControl;		// 이값이 true라면 움직일 수 없다.
	bool _stop;
	bool _isItem;	 // 인벤 사용한다면  
public:
	playerEric();
	~playerEric();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();
	virtual void key();

	void ericFrameCount();
	void ericJump();
	void ericAttack();
	void ericAttackMove();
	void ericHit();
	void setEricImage();
	
	tagPlayer getEric() { return _eric; }	 // ERIC 
	RECT getEricRect() { return _eric.rc; }
	void setEricX(float x) { _eric.x = x; }
	void setEricY(float y) { _eric.y = y; }
	void setEricPosState(tagPosState posstate) {	_eric.posState = posstate; }
	void PixelCollision();			// Y축 충돌 처리 
	void PixelRightCollision();		// X축 오른쪽 충돌 처리 
	void PixelLeftCollision();		// X축 왼쪽   충돌 처리 
	void isJumpPixelCollision();	// 점프시 충돌 처리 
	void setHit() { _isHit = true; }
	bool getHit() { return _isHit; }
	void setEricHP() { _eric.hp++; }
	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _eric.isDead = true; } // 지울 예정 
	void setEricUnable() { _ericUnable = true;	}
	void setEricStop() { _stop = true; }
	void setEricFrame() { _eric.currentFrameX = 0; }
	void setEricJump() { _ericJump = false; }
	void setEricJumpPower() { _eric.jumpPower = 14;  }
	void setEricFrameSpeed(int speed) {	_eric.frameSpeed = speed; }
	void ericDie();

	void setEricState(tagState state) { _eric.state = state; }	// 상태를 정의해 주는 세터 


	void setEricHit() { _eric.hp--; }

	void setItemKey() { _isItem ? _isItem = false : _isItem = true; }

	bool getItem() { return _isItem; }

};

