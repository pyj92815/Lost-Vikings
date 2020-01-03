#pragma once
#include "gameNode.h"
#include "playerEric.h"
#include "playerbaleog.h"
#include "PlayerOlaf.h"
#include "worldObjects.h"


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

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

struct tagInven
{
	image* image;
	tagTypeItem typeItem;
	int player;			  // 0 1 2 값으로 사용자를 판단 
	int invenNumber;	  // 0 1 2 3 (4 = 쓰레기통)
	bool choice;
};

class playerManager : public gameNode
{
private:
	playerEric* _eric;
	playerbaleog* _baleog;
	PlayerOlaf* _olaf;
	vector<tagInven>		    _vInven;
	vector<tagInven>::iterator _viInven;

	int _direction[3];  // player, invenNumber 
	int _itemNum;
	int	_playing;  // 0 eric 1 baleog 2 olaf
	int _itemCount[3]; // 0 1 2
	worldObjects* _wo;

	bool _trade;

public:
	playerManager() {}
	~playerManager() {}

	HRESULT init();
	void update();
	void release();
	void render();

	vector<tagInven>		   get_vInven()		{ return _vInven;    }
	vector<tagInven>::iterator get_viInven()	{ return _viInven;   }
	int*				   getItemNum()  { return _direction; }

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

	void itemUse();
	void trapColision();
	void itemColision();
	void boradColision();
	void removeInven(int Num) { _vInven.erase(_vInven.begin() + Num); }

};

