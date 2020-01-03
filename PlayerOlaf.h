#pragma once
#include "gameNode.h"
#include "Player.h"

#define GRAVITY 0.2f
#define PLAYER_SPEED 5

class PlayerOlaf : public gameNode
{
private:
	tagPlayer _olaf;
	int _olafStateTemp;
	int _olafPosStateTemp;

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
	bool _stopControl;

public:
	PlayerOlaf();
	~PlayerOlaf();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void init_SettingOlafImg();
	void UpdateFrame();
	void KeyControl();
	void SetOlafState();
	void SetOlafPosState();
	void PixelCollision();
	void ResetAnimation1();
	void ResetAnimation2();

	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _olaf.isDead = true; } // 지울 예정
	RECT GetOlafRC() { return _olaf.rc; }
	bool GetOlafShieldState() { return _isShieldUp; }
	tagPlayer getOlaf() { return _olaf; }
	void Set_OlafState(tagState state) { _olaf.state = state; }	// 상태를 정의해 주는 세터 
};