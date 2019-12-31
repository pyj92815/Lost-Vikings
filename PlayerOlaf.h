#pragma once
#include "gameNode.h"
#include "Player.h"

#define GRAVITY 0.04f
#define PLAYER_SPEED 5

class PlayerOlaf : public gameNode
{
private:
	tagPlayer _olaf;
	float _probeY_Top;
	float _probeY_Bottom;
	bool _isShieldUp;
	RECT _shield;
	POINTFLOAT _shieldPos;
	POINTFLOAT _shieldRadius;

	COLORREF getPixel_BC;
	int r_BC;
	int g_BC;
	int b_BC;

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