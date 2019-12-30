#pragma once
#include "gameNode.h"
#include "playerEric.h"
#include "playerbaleog.h"


class playerManager : public gameNode
{
private:
	playerEric* _eric;
	playerbaleog* _baleog;

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void update();
	void release();
	void render();

	tagPlayer getPlayerEric() { return _eric->getEric(); }
	tagPlayer getPlayerBaleog() { return _baleog->getBaleog(); }

	void setColisionFloor(); // �ٴ� �浹 
};

