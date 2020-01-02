#include "stdafx.h"
#include "worldObjects.h"
#include "playerManager.h"

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
	for (int i = 0; i < 3; i++)
	{
		_waterFall[i].frameX = 0;
		_waterFall[i].image = IMAGEMANAGER->findImage("smallWater_Fall");
	}
	//■■■■■■■■■■■■■■■■■벽 및 발판 위치■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	_isUpDown = false;
	IMAGEMANAGER->addImage("Stone_Door_5", "./image/ImageCollection/Stone_Door_5.bmp", 48, 243, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Stone_Door_4", "./image/ImageCollection/Stone_Door_4.bmp", 48, 192, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("BrownDoor_1", "./image/ImageCollection/BrownDoor.bmp", 45, 195, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("BrownDoor_2", "./image/ImageCollection/BrownDoor.bmp", 45, 195, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Moving_Flatform", "./image/ImageCollection/Moving_Flatform.bmp", 192, 45, false, RGB(0, 0, 0));
	_flyingBoard.rc = RectMake(1679, 325, 192, 45);
	_breakableWallOne.rc = RectMake(1324, 225, 48, 243);
	_breakableWallTwo.rc = RectMake(3055, 85, 48, 192);
	_unbreakableWallOne.rc = RectMake(2090, 85, 45, 195);
	_unbreakableWallTwo.rc = RectMake(3695, 2055, 45, 195);
	//■■■■■■■■■■■■■■■■■아이템 위치■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

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
		1150, 132, _waterFall[0].frameX, _waterFall[0].frameY);
	//■■■■■■■■■■■■■■■■■벽 및 발판■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->findImage("Stone_Door_5")->render(CAMERAMANAGER->getWorDC(), _breakableWallOne.rc.left, _breakableWallOne.rc.top);
	IMAGEMANAGER->findImage("Stone_Door_4")->render(CAMERAMANAGER->getWorDC(), _breakableWallTwo.rc.left, _breakableWallTwo.rc.top);
	IMAGEMANAGER->findImage("BrownDoor_1")->render(CAMERAMANAGER->getWorDC(), _unbreakableWallOne.rc.left, _unbreakableWallOne.rc.top);
	IMAGEMANAGER->findImage("BrownDoor_2")->render(CAMERAMANAGER->getWorDC(), _unbreakableWallTwo.rc.left, _unbreakableWallTwo.rc.top);
	IMAGEMANAGER->findImage("Moving_Flatform")->render(CAMERAMANAGER->getWorDC(), _flyingBoard.rc.left, _flyingBoard.rc.top);
	if (KEYMANAGER->isStayKeyDown('Q'))
	{//■■■■■■■■■■■■■■■■■벽 및 발판 충돌 렉트■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		Rectangle(CAMERAMANAGER->getWorDC(), _flyingBoard.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _breakableWallOne.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _breakableWallTwo.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _unbreakableWallOne.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _unbreakableWallTwo.rc);
	}
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
			if (_poision[0].frameX >= 5) { _poision[0].rc = RectMake(1307, 1150, 26, 34); }
			if (_poision[1].frameX >= 5) { _poision[1].rc = RectMake(1550, 1150, 26, 34); }
			if (_poision[2].frameX >= 5) { _poision[2].rc = RectMake(1985, 1150, 26, 34); }
			if (_poision[3].frameX >= 5) { _poision[3].rc = RectMake(2470, 1350, 26, 34); }
		}
	}
	//■■■■■■■■■■■■■■■■■폭포 함정■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	if (_frameCount % 3 == 0)
	{
		_waterFall[0].image->setFrameX(_waterFall[0].frameX);
		_waterFall[0].frameX++;
		if (_waterFall[0].frameX > _waterFall[0].image->getMaxFrameX()) { _waterFall[0].frameX = 0; }
	}
	//■■■■■■■■■■■■■■■■■아이템■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
}

void worldObjects::move()
{
	//■■■■■■■■■■■■■■■■■독 함정■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	RECT temp;
	for (int i = 0; i < 4; i++)
	{
		if (!IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
		{
			_poision[i].rc.top += 5;
			_poision[i].rc.bottom += 5;
		}
	}
	//■■■■■■■■■■■■■■■■■벽 및 발판■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	if (!_isUpDown)
	{
		_flyingBoard.rc.top += 3;
		_flyingBoard.rc.bottom += 3;
		if(_flyingBoard.rc.bottom >= 625 )
		{
			_isUpDown = true;
		}
	}
	if (_isUpDown)
	{
		_flyingBoard.rc.top -= 3;
		_flyingBoard.rc.bottom -= 3;
		if (_flyingBoard.rc.top <= 85)
		{
			_isUpDown = false;
		}
	}

}