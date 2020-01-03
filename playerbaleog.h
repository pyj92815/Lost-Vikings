#pragma once
#include "gameNode.h"
#include "player.h"
#include <vector>
#define PI 3.141592654
#define BALEOG_SPEED 5



enum ARROWSTATE
{
	SHOT,
	FIRE_SHOT
};
struct tagArrow
{
	image* arrowImage;				//화살 이미지 공간
	RECT rc;						//화살 렉트
	float x, y;						//화살 좌표
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	bool isFire;
	int count;
	int direction;
};

class arrow : public gameNode				//화살 클래스
{
private:
	vector<tagArrow> _vArrow;				//화살 담을 백터
	vector<tagArrow>::iterator _viArrow;	//이터레이터
	float _range;							//사거리
	int _arrowMax;							//최대 갯수
	int _direction;							//방향
	ARROWSTATE _arrowState;					//화살 종류

public:
	arrow() {};
	~arrow() {};
	virtual HRESULT init(int arrowMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float speed, float angle, int direction);
	void removeArrow(int arrNum);
	void arrowMove(bool fire);

	vector<tagArrow> getVArrow() { return _vArrow; }
	vector<tagArrow>::iterator getViArrow() { return _viArrow; }


};

class playerbaleog : public player	//벨로그 클래스
{

private:
	tagPlayer _baleog;				//플레이어 태그			
	bool _baleogAttackMotion;		//불값이 켜지면 칼공격2, 꺼지면 칼공격1이 나온다.
	bool _pullString;				//활시위를 땡겼을 때 유지하는 불값
	bool _notMove;					//공격을 할 때 이동을 금지하게 하는 불값			

	float _probeY;
	float _moveSpeed;

	arrow* _ar;						//화살 클래스를 포인터로 가리킨다

	bool _stopControl;		// 이값이 true라면 움직일 수 없다.


	COLORREF getPixel_BC;
	int r_BC;
	int g_BC;
	int b_BC;

	COLORREF getPixel_TC;
	int r_TC;
	int g_TC;
	int b_TC;

	RECT _testRect;



public:
	playerbaleog();
	~playerbaleog();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void key();									//조작키 함수
	void setBaleogState();						//상태에 이미지 찾아주는 함수
	void PixelCollision();						//픽셀 충돌 함수
	void SetBaleogPosState();					//큰범위 상태에 이미지 찾아주는 함수

	void baleogDie();


	tagPlayer getBaleog() { return _baleog; }

	void hgKey();	// 형길이가 쓰는 비밀 이동키
	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _baleog.isDead = true; }

	//void PixelCollision();			// Y축 충돌 처리 
	void PixelRightCollision();		// X축 오른쪽 충돌 처리 
	void PixelLeftCollision();		// X축 왼쪽   충돌 처리 
};



