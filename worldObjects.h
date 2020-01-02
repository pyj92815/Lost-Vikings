#pragma once
#include "gameNode.h"

class playerManager;
enum tagType
{
	TYPE_BOMB,
	TYPE_TOMATO,
	TYPE_TOMATO2,
	TYPE_REDKEY,
	TYPE_REDLOCKER,
	TYPE_BLUEKEY,
	TYPE_BLUELOCKER,
};

struct tagObjects
{
	tagType itemType;
	RECT rc;				//오브젝트(함정/맵 장식 등)
	image* image;
	bool isCollision;		//함정과 플레이어가 만났는지 아닌지
	//프레임 x,y 값
	int frameX;
	int frameY;
	int maxFrameX;			//최대 프레임값
};
class worldObjects : public gameNode
{
private:
	//■■■■■■■■■■■가시 함정■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _niddle[3];
private:
	//■■■■■■■■■■■독 함정■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _poision[4];
	bool _isntColliToNiddle;
	int _poisionCount;
private:
	//■■■■■■■■■■■벽 및 발판■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _flyingBoard;
	bool _isUpDown;
	tagObjects _breakableWallOne;
	tagObjects _breakableWallTwo;
	tagObjects _unbreakableWallOne;
	tagObjects _unbreakableWallTwo;
private:
	//■■■■■■■■■■■폭포■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _waterFall[3];
private:
	//■■■■■■■■■■■아이템■■■■■■■■■■■■■■■■■■■■■■
	vector<tagObjects>				  _vItem;
	vector<tagObjects>::iterator	 _viItem;
	
	playerManager* _pm;
	/*tagObjects _Boom;
	tagObjects _redKey;
	tagObjects _redLocker;
	tagObjects _blueKey;
	tagObjects _blueLocker;
	tagObjects _tomato;*/

private:
	int _frameCount;
public:
	worldObjects();
	~worldObjects();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	vector<tagObjects> get_vItem() { return _vItem; }
	vector<tagObjects>::iterator get_viItem() { return _viItem; }

	virtual void framework();
	virtual void move();

	void setPlayerManagerAddressLink(playerManager* pm) { _pm = pm; }


};

