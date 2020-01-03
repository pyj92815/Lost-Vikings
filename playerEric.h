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
	bool _ericUnable;		// ���� �Ҵ� ����
	bool _isHit;
	bool _isBreath;
	bool _isSlide;
	bool _isSlideOn;
	int _hitCount;
	int _breathCount;
	int _breathFrameCount;
	int _slideCount; // �����̵� ī��Ʈ 
	float _jumpStart;
	float _gravity;
	float _slidePower;

	bool  _stopControl;		// �̰��� true��� ������ �� ����.
	bool _stop;
	bool _isItem;	 // �κ� ����Ѵٸ�  
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
	void PixelCollision();			// Y�� �浹 ó�� 
	void PixelRightCollision();		// X�� ������ �浹 ó�� 
	void PixelLeftCollision();		// X�� ����   �浹 ó�� 
	void isJumpPixelCollision();	// ������ �浹 ó�� 
	void setHit() { _isHit = true; }
	bool getHit() { return _isHit; }
	void setEricHP() { _eric.hp++; }
	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _eric.isDead = true; } // ���� ���� 
	void setEricUnable() { _ericUnable = true;	}
	void setEricStop() { _stop = true; }
	void setEricFrame() { _eric.currentFrameX = 0; }
	void setEricJump() { _ericJump = false; }
	void setEricJumpPower() { _eric.jumpPower = 14;  }
	void setEricFrameSpeed(int speed) {	_eric.frameSpeed = speed; }
	void ericDie();

	void setEricState(tagState state) { _eric.state = state; }	// ���¸� ������ �ִ� ���� 


	void setEricHit() { _eric.hp--; }

	void setItemKey() { _isItem ? _isItem = false : _isItem = true; }

	bool getItem() { return _isItem; }

};

