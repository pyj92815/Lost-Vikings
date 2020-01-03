#pragma once
#include "gameNode.h"
#include "playerEric.h"
#include "playerbaleog.h"
#include "PlayerOlaf.h"


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

class EnemyManager;
class worldObjects;
// �÷��̾��� Ÿ��
enum PLAYER_TYPE
{
	PT_Eric,
	PT_Baleog,
	PT_Olaf
};

enum tagTypeDie
{
	TYPE_DIE,		 // �⺻ �״� ��� 
	TYPE_FLYDIE,	 // ���� 
	TYPE_PRESS,      // ������ 
	TYPE_POISION,	 // ��
};

struct tagInven
{
	image* image;
	int player;			  // 0 1 2 ������ ����ڸ� �Ǵ� 
	int invenNumber;	  // 0 1 2 3 (4 = ��������)
};

class playerManager : public gameNode
{
private:
	playerEric* _eric;
	playerbaleog* _baleog;
	PlayerOlaf* _olaf;

	arrow* _arrow;

	vector<tagInven>		    _vInven;
	vector<tagInven>::iterator _viInven;

	tagInven _direction;  // player, invenNumber 



	int	_playing;  // 0 eric 1 baleog 2 olaf
	int _itemCount[3]; // 0 1 2
	worldObjects* _wo;

	EnemyManager* _em;


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

	arrow* arrowOne() {	return _arrow;}

	void set_Playing(int playChar) { _playing = playChar; }
	void KILLPlayer();

	int getPlaying() { return _playing; }
	void itemKey();
	void setWorldObjectAddressLink(worldObjects* wo) { _wo = wo; }
	void setMemoryAddressLink(EnemyManager* em) { _em = em; }

	void trapColision();
	void itemColision();
	void boradColision();

	void enemyColision();

};

