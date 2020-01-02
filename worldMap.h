#pragma once
#include "gameNode.h"
#include "worldObjects.h"

class worldMap : public gameNode
{

private:
	worldObjects* _wo;
public:
	worldMap();
	~worldMap();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	worldObjects* getWorldObject() { return _wo; }

};

