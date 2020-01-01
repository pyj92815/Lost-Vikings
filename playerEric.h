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

	void PixelCollision();			// Y�� �浹 ó�� 
	void PixelRightCollision();		// X�� ������ �浹 ó�� 
	void PixelLeftCollision();		// X�� ����   �浹 ó�� 
	void isJumpPixelCollision();	// ������ �浹 ó�� 

	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _eric.isDead = true; } // ���� ���� 

	void ericDie();
	void setEricState(tagState state) { _eric.state = state; }	// ���¸� ������ �ִ� ���� 
};

