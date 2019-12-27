#pragma once
#include "gameNode.h"
#include "playerEric.h"


class playerManager : public gameNode
{
private:
	playerEric* _eric;

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void update();
	void release();
	void render();

	tagPlayer getPlayerEric() { return _eric->getEric(); }
};


