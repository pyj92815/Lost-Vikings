#pragma once
#include "gameNode.h"

struct tagObjects
{
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
	tagObjects _niddle[2];
private:
	//■■■■■■■■■■■독 함정■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _poision[3];
	bool _isntColliToNiddle;
	int _poisionCount;
private:
	//■■■■■■■■■■■반판■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _flyingBoard[1];
private:
	//■■■■■■■■■■■폭포■■■■■■■■■■■■■■■■■■■■■■
	tagObjects _waterFall[2];
private:
	int _frameCount;
public:
	worldObjects();
	~worldObjects();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void collision(int x, int y);

	virtual void framework();
	virtual void move();
};

