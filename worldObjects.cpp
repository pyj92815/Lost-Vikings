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
	for (int i = 0;i < 3;i++)
	{
		_niddle[i].trap = TRAP_NIDDLE;
		_niddle[i].isCollision = false;
	}
	
	//■■■■■■■■■■■■■■■■■독 함정 위치 렉트■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->addFrameImage("poision", "./image/ImageCollection/poision.bmp", 130, 56, 5, 1, true, RGB(255, 0, 255));

	_poision[0].x = 1307;
	_poision[1].x = 1550;
	_poision[2].x = 1985;
	_poision[3].x = 2470;
	_poision[0].y = 1150;
	_poision[1].y = 1150;
	_poision[2].y = 1150;
	_poision[3].y = 1350;
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
		_poision[i].isCollision = false;
		_poision[i].trap = TRAP_POISION;
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
	_flyingBoard.image = IMAGEMANAGER->addImage("Moving_Flatform", "./image/ImageCollection/Moving_Flatform.bmp", 192, 45, false, RGB(0, 0, 0));
	_flyingBoard.rc = RectMake(1679, 325, 192, 45);
	_flyingBoard.x = 1679;
	_flyingBoard.y = 325;
	_flyingBoard.trap = TRAP_BORAD;
	_breakableWallOne.rc = RectMake(1324, 225, 48, 243);
	_breakableWallTwo.rc = RectMake(3055, 85, 48, 192);
	_unbreakableWallOne.rc = RectMake(2090, 85, 45, 195);
	_unbreakableWallTwo.rc = RectMake(3695, 2055, 45, 195);

	_vTrap.push_back(_flyingBoard);

	for (int i = 0;i < 3;i++)
	{
		_vTrap.push_back(_niddle[i]);
	}
	for (int i = 0;i < 4;i++)
	{
		_vTrap.push_back(_poision[i]);
	}
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

	for (_viTrap = _vTrap.begin();_viTrap != _vTrap.end(); ++_viTrap)
	{
		if (_viTrap->trap == TRAP_POISION)
		{
			_viTrap->rc = RectMake(_viTrap->x, _viTrap->y + (_viTrap->image->getFrameHeight()/2)
				, _viTrap->image->getFrameWidth(), _viTrap->image->getFrameHeight() / 2);
		}
		else if(_viTrap->trap == TRAP_BORAD)
		{
			_viTrap->rc = RectMake(_viTrap->x, _viTrap->y, 192, 45);
		}
	}
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
	//for (int i = 0; i < 4; i++)
	//{
	//	Rectangle(CAMERAMANAGER->getWorDC(), _poision[i].rc);
	//	IMAGEMANAGER->findImage("poision")->frameRender(CAMERAMANAGER->getWorDC(),
	//		_poision[i].rc.left, _poision[i].rc.top - 20, _poision[i].frameX, _poision[i].frameY);
	//}
	//■■■■■■■■■■■■■■■■■폭포■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->findImage("smallWater_Fall")->frameRender(CAMERAMANAGER->getWorDC(),
		1150, 132, _waterFall[0].frameX, _waterFall[0].frameY);
	//■■■■■■■■■■■■■■■■■벽 및 발판■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	IMAGEMANAGER->findImage("Stone_Door_5")->render(CAMERAMANAGER->getWorDC(), _breakableWallOne.rc.left, _breakableWallOne.rc.top);
	IMAGEMANAGER->findImage("Stone_Door_4")->render(CAMERAMANAGER->getWorDC(), _breakableWallTwo.rc.left, _breakableWallTwo.rc.top);
	IMAGEMANAGER->findImage("BrownDoor_1")->render(CAMERAMANAGER->getWorDC(), _unbreakableWallOne.rc.left, _unbreakableWallOne.rc.top);
	IMAGEMANAGER->findImage("BrownDoor_2")->render(CAMERAMANAGER->getWorDC(), _unbreakableWallTwo.rc.left, _unbreakableWallTwo.rc.top);
	//IMAGEMANAGER->findImage("Moving_Flatform")->render(CAMERAMANAGER->getWorDC(), _flyingBoard.rc.left, _flyingBoard.rc.top);
	if (KEYMANAGER->isStayKeyDown('Q'))
	{//■■■■■■■■■■■■■■■■■벽 및 발판 충돌 렉트■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		Rectangle(CAMERAMANAGER->getWorDC(), _breakableWallOne.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _breakableWallTwo.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _unbreakableWallOne.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _unbreakableWallTwo.rc);
	}
	for (_viTrap = _vTrap.begin();_viTrap != _vTrap.end(); ++_viTrap)
	{
		if (_viTrap->trap == TRAP_POISION)
		{
			if (!_viTrap->isCollision)
			{
				Rectangle(CAMERAMANAGER->getWorDC(), _viTrap->rc);
				_viTrap->image->frameRender(CAMERAMANAGER->getWorDC(), _viTrap->x, _viTrap->y, _viTrap->frameX, _viTrap->frameY);
			}
		}
		else if (_viTrap->trap == TRAP_BORAD)
		{
			_viTrap->image->render(CAMERAMANAGER->getWorDC(), _viTrap->x, _viTrap->y);
			//Rectangle(CAMERAMANAGER->getWorDC(), _viTrap->rc);
		}
	}
}

void worldObjects::framework()
{
	//■■■■■■■■■■■■■■■■■가시 함정 프레임■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	RECT temp;
	for (_viTrap = _vTrap.begin();_viTrap != _vTrap.end(); ++_viTrap)
	{
		if (_frameCount % 2 == 0)
		{
			if (_viTrap->trap == TRAP_POISION)
			{
				if (!IntersectRect(&temp, &_viTrap->rc, &_niddle[1].rc))
				{
					_viTrap->image->setFrameX(_viTrap->frameX);
					if (_viTrap->frameX >= 0) {	_viTrap->frameX = 0;}
				}
				else if(IntersectRect(&temp, &_viTrap->rc, &_niddle[1].rc))
				{
					_viTrap->image->setFrameX(_viTrap->frameX);
					_viTrap->frameX++;
				}
				if (_viTrap->frameX > _viTrap->image->getMaxFrameX()) 
				{
					_viTrap->y = 1150;
					_viTrap->isCollision = false;
				}
			}
		}
	}

	//for (int i = 0; i < 4; i++)
	//{
	//	if (_frameCount % 2 == 0)
	//	{
	//		//■■■■■■■■■■■■■■■■■독이 가시와 충돌하지 않았다면■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//		if (!IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
	//		{
	//			_poision[i].image->setFrameX(_poision[i].frameX);
	//			if (_poision[i].frameX >= 0) { _poision[i].frameX = 0; }
	//		}//■■■■■■■■■■■■■■■■■독이 가시와 충돌했다면■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//		else if (IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
	//		{
	//			_poision[i].image->setFrameX(_poision[i].frameX);
	//			_poision[i].frameX++;
	//		}
	//		if (_poision[0].frameX >= 5) { _poision[0].rc = RectMake(1307, 1150, 26, 34); }
	//		if (_poision[1].frameX >= 5) { _poision[1].rc = RectMake(1550, 1150, 26, 34); }
	//		if (_poision[2].frameX >= 5) { _poision[2].rc = RectMake(1985, 1150, 26, 34); }
	//		if (_poision[3].frameX >= 5) { _poision[3].rc = RectMake(2470, 1350, 26, 34); }
	//	}
	//}
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
	for (_viTrap = _vTrap.begin();_viTrap != _vTrap.end(); ++_viTrap)
	{
		if (_viTrap->trap == TRAP_POISION)
		{
			if (!IntersectRect(&temp, &_viTrap->rc, &_niddle[1].rc))
			{
				_viTrap->y += 5;
			}
		}
		else if (_viTrap->trap == TRAP_BORAD)
		{
			if (!_isUpDown)
			{
				_viTrap->y += 3;
				if (_viTrap->y +45 >= 625)
				{
					_isUpDown = true;
				}
			}
			if (_isUpDown)
			{
				_viTrap->y -= 3;
				if (_viTrap->y <= 85)
				{
					_isUpDown = false;
				}
			}
		}
	}
	//for (int i = 0; i < 4; i++)
	//{
	//	if (!IntersectRect(&temp, &_poision[i].rc, &_niddle[1].rc))
	//	{
	//		_poision[i].rc.top += 5;
	//		_poision[i].rc.bottom += 5;
	//	}
	//}
	//■■■■■■■■■■■■■■■■■벽 및 발판■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	

}