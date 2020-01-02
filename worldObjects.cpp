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
	IMAGEMANAGER->addFrameImage("poision", "./image/ImageCollection/poision.bmp", 130, 56, 5, 1, true, RGB(255, 0, 255));
	_poision[0].rc = RectMake(1307, 1150, 26, 34);
	_poision[1].rc = RectMake(1550, 1150, 26, 34);
	_poision[2].rc = RectMake(1985, 1150, 26, 34);
	_poision[3].rc = RectMake(2470, 1350, 26, 34);
	for (int i = 0; i < 4; i++)
	{
		_poision[i].frameX = 0;
		_poision[i].frameY = 0;
		_poision[i].image = new image;
		_poision[i].image = IMAGEMANAGER->findImage("poision");
	}
	//■■■■■■■■■■■■■■■■■폭포 위치 렉트■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->addFrameImage("smallWater_Fall", "./image/ImageCollection/water_Fall.bmp", 588, 650, 4, 1, true, RGB(255, 0, 255));
	_waterFall[0].rc = RectMake(1200, 62, 147, 650);
	for (int i = 0; i < 3; i++)
	{
		_waterFall[i].frameX = 0;
		_waterFall[i].image = IMAGEMANAGER->findImage("smallWater_Fall");
	}
	//■■■■■■■■■■■■■■■■■■■■여러가지■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_frameCount = 0;
	return S_OK;
}

void worldObjects::update()
{
	_frameCount++;
	//_poisionCount++;
	move();
	framework();
}

void worldObjects::release()
{
}

void worldObjects::render()
{
	//■■■■■■■■■■■■■■■■■가시 함정■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < 3; i++)
	{
		Rectangle(CAMERAMANAGER->getWorDC(), _niddle[i].rc);
	}
	//■■■■■■■■■■■■■■■■■독 함정■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	for (int i = 0; i < 4; i++)
	{
		Rectangle(CAMERAMANAGER->getWorDC(), _poision[i].rc);
		IMAGEMANAGER->findImage("poision")->frameRender(CAMERAMANAGER->getWorDC(),
			_poision[i].rc.left, _poision[i].rc.top - 20, _poision[i].frameX, _poision[i].frameY);
	}
	//■■■■■■■■■■■■■■■■■폭포■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->findImage("smallWater_Fall")->frameRender(CAMERAMANAGER->getWorDC(),
		_waterFall[0].rc.left - 50, _waterFall[0].rc.top + 70, _waterFall[0].frameX, _waterFall[0].frameY);
}

void worldObjects::collision(int x, int y)
{

}

void worldObjects::framework()
{
	//■■■■■■■■■■■■■■■■■가시 함정 프레임■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	RECT temp;
	for (int i = 0; i < 4; i++)
	{
		if (_frameCount % 2 == 0)
		{
			//■■■■■■■■■■■■■■■■■독이 가시와 충돌하지 않았다면■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
			if (!IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
			{
				_poision[i].image->setFrameX(_poision[i].frameX);
				if (_poision[i].frameX >= 0) { _poision[i].frameX = 0; }
			}//■■■■■■■■■■■■■■■■■독이 가시와 충돌했다면■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
			else if (IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
			{
				_poision[i].image->setFrameX(_poision[i].frameX);
				_poision[i].frameX++;
			}
			if (_poision[i].frameX >= 5)
			{ 
				_poision[0].rc = RectMake(1307, 1150, 26, 34);
				_poision[1].rc = RectMake(1550, 1150, 26, 34);
				_poision[2].rc = RectMake(1985, 1150, 26, 34);
				_poision[3].rc = RectMake(2470, 1350, 26, 34);
			}
		}
	}

	//■■■■■■■■■■■■■■■■■폭포 함정■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	if (_frameCount % 3 == 0)
	{
		_waterFall[0].image->setFrameX(_waterFall[0].frameX);
		_waterFall[0].frameX++;
		if (_waterFall[0].frameX > _waterFall[0].image->getMaxFrameX()) { _waterFall[0].frameX = 0; }
	}
}

void worldObjects::move()
{
	//TEST
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