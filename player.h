#pragma once
#include "gameNode.h"
enum tagState			// 이미지의 상태값  
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_ERIC_JUMP,	   // 에릭의 특성 
	STATE_ERIC_HEADBUTT,   // 박치기 
	STATE_ERIC_HEADBUTTEND,// 박치기 이후 
	STATE_OLAF_GUARD,	   // 울라프
	STATE_OLAF_FLY,		   // 울라프 날때
	STATE_BALEOG_ARROW_REDY,// 벨로그 화살
	STATE_BALEOG_ARROW_FIRE,
	STATE_BALEOG_ARROW,
	STATE_BALEOG_SWORD,
	STATE_BALEOG_SWORD1,	//벨로그 칼
	STATE_BALEOG_SWORD2,
	STATE_HIT,
	STATE_PUSH,
	STATE_BREATH,
	STATE_DIE,		    // 기본죽음 (체력달았을때)  
	STATE_POISON,		// 독사
	STATE_MIRRA,		// 미라사
	STATE_PRESSDIE,		// 압축사
	STATE_TRAPDIE,		// 뿔에 찔려 죽는사
	// 추가
	STATE_STEPLADDER, // 사다리탈때
	STATE_STEPLADDEREND, // 사다리끝
};

enum tagPosState  // position state
{
	POSSTATE_GROUND,    // 중력을 안받고 
	POSSTATE_AIR,		// 중력을 받는다 
};

struct tagPlayer
{
	tagPosState posState;	 // 위치 
	tagState state;			 // 기본값은 IDLE
	image* image;
	RECT rc;
	float x, y;
	float angle;
	float damage;
	float jumpPower;	 // 에릭만 사용하는 점프 
	float movePower;
	float movePowerCount;
	float gravity;		 // 에릭	  중력		
	float probeY;
	float probeX;
	int direction;		 // FRAME Y 0은 왼쪽, 1은 오른쪽  
	int frameCount;
	int currentFrameX, currentFrameY;
	int frameSpeed;
	int hp;	   // 3개 
	bool isDead;				// 살았는지 죽었는지
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
	TYPE_DIE,		 // 기본 죽는 모션 
	TYPE_FLYDIE,	 // 낙사 
	TYPE_PRESS,      // 프레스 
	TYPE_POISION,	 // 독
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

