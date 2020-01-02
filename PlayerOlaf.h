#pragma once
#include "gameNode.h"
#include "Player.h"

#define GRAVITY 0.04f
#define PLAYER_SPEED 5

class PlayerOlaf : public gameNode
{
private:
	tagPlayer _olaf;
	float _probeX_FixRange; // 사다리 탈 상황에 검색 길이 값 조정하기 위한 변수
	float _probeY_FixRange;
	bool _isShieldUp;
	RECT _shield;
	POINTFLOAT _shieldPos;
	POINTFLOAT _shieldRadius;

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
	PlayerOlaf();
	~PlayerOlaf();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void init_SettingOlafImg();
	void KeyControl();
	void SetOlafState();
	void SetOlafPosState();
	void PixelCollision();

	tagPlayer getOlaf() { return _olaf; }
};