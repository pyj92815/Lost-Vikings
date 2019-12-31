#include "stdafx.h"
#include "worldObjects.h"

worldObjects::worldObjects()
{
}

worldObjects::~worldObjects()
{
}

HRESULT worldObjects::init()
{
	//■■■■■■■■■■■■■■■■■가시 함정 위치 렉트■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_niddle[0].rc = RectMake(240, 2199, 570, 40);
	_niddle[1].rc = RectMake(1111, 2199, 2385, 40);
	_niddle[2].rc = RectMake(1686, 48, 180, 39);
	//■■■■■■■■■■■■■■■■■독 함정 위치 렉트■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_isntColliToNiddle = false;
	IMAGEMANAGER->addFrameImage("poision", "./image/ImageCollection/poision.bmp", 130, 56, 5, 1, true, RGB(255, 0, 255));
	_poision[0].rc = RectMake(1307, 1250, 26, 34);
	for (int i = 0; i < 4; i++)
	{
		_poision[i].frameX = 0;
		_poision[i].frameY = 0;
		_poision[i].image = new image;
		_poision[i].image = IMAGEMANAGER->findImage("poision");
	}
	//■■■■■■■■■■■■■■■■■■■■여러가지■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_frameCount = 0;
	return S_OK;
}

void worldObjects::update()
{
	_frameCount++;
	_poisionCount++;
	move();
	framework();
}

void worldObjects::release()
{
}

void worldObjects::render()
{
	for (int i = 0; i < 3; i++)
	{
		Rectangle(CAMERAMANAGER->getWorDC(), _niddle[i].rc);
	}
	for (int i = 0; i < 4; i++)
	{
		Rectangle(CAMERAMANAGER->getWorDC(), _poision[0].rc);
		IMAGEMANAGER->findImage("poision")->frameRender(CAMERAMANAGER->getWorDC(), 
			_poision[0].rc.left, _poision[0].rc.top - 20,_poision[0].frameX, _poision[0].frameY);
	}
}

void worldObjects::collision(int x, int y)
{

}

void worldObjects::framework()
{
	RECT temp;
	for (int i = 0; i < 4; i++)
	{
		if (_frameCount % 2 == 0)
		{
			//■■■■■■■■■■■■■■■■■독이 가시와 충돌하지 않았다면■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
			if (!IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
			{
				_poision[i].image->setFrameX(_poision[i].frameX);
				_poision[i].frameX++;
				if (_poision[i].frameX >= 0) { _poision[i].frameX = 0; }
			}//■■■■■■■■■■■■■■■■■독이 가시와 충돌했다면■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
			else if (IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
			{
				_poision[i].image->setFrameX(_poision[i].frameX);
				_poision[i].frameX++;
			}
			if (_poision[i].frameX >= 4){ _poision[0].rc = RectMake(1307, 1250, 26, 34); }
		}
	}
}

void worldObjects::move()
{
	RECT temp;
	for (int i = 0; i < 4; i++)
	{
		if (!IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
		{
			_poision[i].rc.top += 5;
			_poision[i].rc.bottom += 5;
		}
	}
}