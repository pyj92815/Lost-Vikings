#pragma once
#include "gameNode.h"

class playerManager;
enum tagTypeItem
{
	ITEM_BOMB,
	ITEM_TOMATO,
	ITEM_TOMATO2,
	ITEM_REDKEY,
	ITEM_REDLOCKER,
	ITEM_BLUEKEY,
	ITEM_BLUELOCKER,
};

enum tagTypeTrap
{
	TRAP_POISION,
	TRAP_NIDDLE,
	TRAP_WALL,
	TRAP_BORAD,
};

struct tagObjects
{
	tagTypeItem item;
	tagTypeTrap trap;
	RECT rc;				//오브젝트(함정/맵 장식 등)
	image* image;
	bool isCollision;		//함정과 플레이어가 만났는지 아닌지
	float x, y;
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
	tagObjects _flyingBoard; // 발판 
	bool _isUpDown;
	tagObjects _breakableWallOne;
	tagObjects _breakableWallTwo;
	tagObjects _unbreakableWallOne;
	tagObjects _unbreakableWallTwo;
private:
	//■■■■■■■■■■■폭포■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _waterFall[3];
private:
	//■■■■■■■■■■■함정■■■■■■■■■■■■■■■■■■■■■■
	vector<tagObjects>				 _vTrap;   // 가시 , 독, 벽, 발판 
	vector<tagObjects>::iterator    _viTrap;

	
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

	vector<tagObjects> get_vTrap()			  { return _vTrap;}
	vector<tagObjects>::iterator get_viTrap()  { return _viTrap;}
	
	vector<tagObjects> get_vItem()			  { return _vItem;}
	vector<tagObjects>::iterator get_viItem() { return _viItem;}
	void setCollision(int arrNum) 
	{ 
		_vTrap[arrNum].isCollision = true; 
	}
	virtual void framework();
	virtual void move();

	void setPlayerManagerAddressLink(playerManager* pm) { _pm = pm; }


};

