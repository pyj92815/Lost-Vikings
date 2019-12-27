#pragma once
#include "gameNode.h"

class worldMap : public gameNode
{
private:

	image* worldImage;
	HDC worldDC;

private:
	image* player;
public:
	worldMap();
	~worldMap();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

