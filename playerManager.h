#pragma once
#include "gameNode.h"
#include "playerEric.h"
#include "playerbaleog.h"
#include "PlayerOlaf.h"
class worldObjects;
// 플레이어의 타입
enum PLAYER_TYPE
{
	PT_Eric,
	PT_Baleog,
	PT_Olaf
};

enum tagTypeDie
{
	TYPE_DIE,		 // 기본 죽는 모션 
	TYPE_FLYDIE,	 // 낙사 
	TYPE_PRESS,      // 프레스 
	TYPE_POISION,	 // 독
};


class playerManager : public gameNode
{
private:
	playerEric* _eric;
	playerbaleog* _baleog;
	PlayerOlaf* _olaf;



	int	_playing;  // 0 eric 1 baleog 2 olaf



	worldObjects* _wo;

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void update();
	void release();
	void render();

	playerEric* getEric() { return _eric; }
	playerbaleog* getbaleog() { return _baleog;}
	PlayerOlaf* getOlaf() { return _olaf; }

	tagPlayer getPlayerEric() { return _eric->getEric(); }
	tagPlayer getPlayerBaleog() { return _baleog->getBaleog(); }
	tagPlayer getPlayerOlaf() { return _olaf->getOlaf(); }

	void set_Playing(int playChar) { _playing = playChar; }
	void KILLPlayer();


	int getPlaying() { return _playing; }
	void itemKey();
	void setWorldObjectAddressLink(worldObjects* wo) { _wo = wo; }


	void trapColision();
	void itemColision();
	void boradColision();

};

