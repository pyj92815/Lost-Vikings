#pragma once
#include"gameNode.h"

enum class EnemyState
{

	IDLE,		//카메라 밖에 있을때 가만히 있는 상태
	SCOUT,		//카메라 안에 들어와서 플레이어를 찾아 정찰하는 상태
	DISCOVERY,	//플레이어가 정찰 범위 안에 들어와 플레이어를 추적하는 상태
	ATTACK,		//플레이어가 공격 범위 안에 들어와서 공격하는 상태
	DIE			//HP가 0이하가 되어 사망한 상태
};

enum class EnemyLR
{
	LEFT,		//적의 이미지 방향을 결정하기 위한 ENUM 
	RIGHT		//				"
};
enum class EnemyType
{
	MUMMY,
	SCORPION,
	SNAKE
};
class Enemy : public gameNode
{
protected:
	//적의 상태 및 이미지 방향을 결정할 ENUM문
	EnemyState _enemyState;
	EnemyLR _enemyLR;
	EnemyType _enemyType;

	//적의 위치를 지정할 변수
	float _x, _y;
	RECT _enemyRect;

	//적의 탐지 범위
	RECT _enemy_DISCOVERY_Rect;

	//카메라의 범위 카메라 안에 적이 들어왔는지 판단하기 위함
	RECT _cameraRect;

	image* _image;

	int _probeX, _probeY;

	int _frameX, _frameY;
	int _frameCount;

	//enemy의 방향을 바꿔주기 위한 bool변수
	bool _turn;


public:

	virtual HRESULT init(EnemyType enemyType, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void EnemyAction();
	virtual void turn();
	virtual void Frame();

	virtual void proveLeft();
	virtual void proveRight();

	virtual EnemyState getEnemyState() { return _enemyState; }
	

	//이미지 추가 함수
	virtual void imageReset()
	{
		IMAGEMANAGER->addFrameImage("Enemy_Mummy", "./image./Enemy/Enemy_Mummy.bmp", 696, 224, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Mummy_Attack", "./image./Enemy/Enemy_Mummy_Attack.bmp", 672, 256, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Scorpion", "./image./Enemy/Enemy_Scorpion.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Scorpion_Attack", "./image./Enemy/Enemy_Scorpion_Attack.bmp", 980, 248, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Snake", "./image./Enemy/Enemy_Snake.bmp", 288, 16, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Snake_Attack", "./image./Enemy/Enemy_Snake_Attack", 765, 120, 9, 2, true, RGB(255, 0, 255));
	}
};

