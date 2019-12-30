#pragma once
#include "gameNode.h"
#include "Player.h"

#define GRAVITY 0.04f
#define PLAYER_SPEED 3

class PlayerOlaf : public gameNode
{
private:
	tagPlayer _olaf;
	float _probeY;
	bool _isShieldUp;
	RECT _shield;
	POINTFLOAT _shieldPos;
	POINTFLOAT _shieldRadius;

public:
	PlayerOlaf();
	~PlayerOlaf();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void KeyControl();
	void SetOlafState();
	void SetOlafPosState();
	void PixelCollision();

	tagPlayer getOlaf() { return _olaf; }
};