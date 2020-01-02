#pragma once
#include "gameNode.h"
enum tagState			// �̹����� ���°�  
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_ERIC_JUMP,	   // ������ Ư�� 
	STATE_ERIC_HEADBUTT,   // ��ġ�� 
	STATE_ERIC_HEADBUTTEND,// ��ġ�� ���� 
	STATE_OLAF_GUARD,	   // �����
	STATE_OLAF_FLY,		   // ����� ����
	STATE_BALEOG_ARROW_REDY,// ���α� ȭ��
	STATE_BALEOG_ARROW_FIRE,
	STATE_BALEOG_ARROW,
	STATE_BALEOG_SWORD,
	STATE_BALEOG_SWORD1,	//���α� Į
	STATE_BALEOG_SWORD2,
	STATE_HIT,
	STATE_PUSH,
	STATE_BREATH,
	STATE_DIE,		    // �⺻���� (ü�´޾�����)  
	STATE_POISON,		// ����
	STATE_MIRRA,		// �̶��
	STATE_PRESSDIE,		// �����
	STATE_TRAPDIE,		// �Կ� ��� �״»�
	// �߰�
	STATE_STEPLADDER, // ��ٸ�Ż��
	STATE_STEPLADDEREND, // ��ٸ���
};

enum tagPosState  // position state
{
	POSSTATE_GROUND,    // �߷��� �ȹް� 
	POSSTATE_AIR,		// �߷��� �޴´� 
};

struct tagPlayer
{
	tagPosState posState;	 // ��ġ 
	tagState state;			 // �⺻���� IDLE
	image* image;
	RECT rc;
	float x, y;
	float angle;
	float damage;
	float jumpPower;	 // ������ ����ϴ� ���� 
	float movePower;
	float movePowerCount;
	float gravity;		 // ����	  �߷�		
	float probeY;
	float probeX;
	int direction;		 // FRAME Y 0�� ����, 1�� ������  
	int frameCount;
	int currentFrameX, currentFrameY;
	int frameSpeed;
	int hp;	   // 3�� 
	bool isDead;				// ��Ҵ��� �׾�����
};

//

enum tagItem
{
	ITME_HP,	 // HP Item 
	ITME_HP2,
	ITME_FIRE,
	ITME_KEY,
};

enum tagTypeDie
{
	TYPE_DIE,		 // �⺻ �״� ��� 
	TYPE_FLYDIE,	 // ���� 
	TYPE_PRESS,      // ������ 
	TYPE_POISION,	 // ��
};


class player :public gameNode
{


public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();
	virtual void key();
};

