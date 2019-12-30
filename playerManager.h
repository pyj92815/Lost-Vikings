#pragma once
#include "gameNode.h"
#include "playerEric.h"
#include "playerbaleog.h"
#include "PlayerOlaf.h"

class playerManager : public gameNode
{
private:
	playerEric* _eric;
	playerbaleog* _baleog;
	PlayerOlaf* _olaf;

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void update();
	void release();
	void render();

	tagPlayer getPlayerEric() { return _eric->getEric(); }
	tagPlayer getPlayerBaleog() { return _baleog->getBaleog(); }
	tagPlayer getPlayerOlaf() { return _olaf->getOlaf(); }

	void setColisionFloor(); // ¹Ù´Ú Ãæµ¹ 
};

