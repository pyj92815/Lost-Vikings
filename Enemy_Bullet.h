#pragma once
#include"gameNode.h"
class Enemy_Bullet :public gameNode
{
private:
	image* _image;
	float _x, _y;
	float _angle;
	RECT _rect;
	float _probeX, _probeY;
	



public:
	bool _isFire;

	HRESULT init(float x1, float y1, float x2,float y2);
	void release();
	void update();
	void render();

	void bulletMove();
	void probe();

	bool bulletRemove() { if (!_isFire)return true; else return false; }

	RECT getRect() { return _rect; }
};

