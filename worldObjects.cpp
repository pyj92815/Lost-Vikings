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
	//�����������������ᰡ�� ���� ��ġ ��Ʈ��������������������������������������������
	_niddle[0].rc = RectMake(240, 2210, 570, 40);
	_niddle[1].rc = RectMake(1111, 2210, 2385, 40);
	_niddle[2].rc = RectMake(1686, 38, 180, 39);
	for (int i = 0;i < 3;i++)
	{//���� Ÿ��
		_niddle[i].trap = TRAP_NIDDLE;
		_niddle[i].isCollision = false;
	}//�������������డ�� ������ ���Ϳ� ���ڡ�������������������
	for (int i = 0;i < 3;i++) { _vTrap.push_back(_niddle[i]); }
	//�����������������ᵶ ���� ��ġ ��Ʈ��������������������������������������������
	IMAGEMANAGER->addFrameImage("poision", "./image/ImageCollection/poision.bmp", 130, 56, 5, 1, true, RGB(255, 0, 255));
	//��ǥ
	_poision[0].x = 1307;
	_poision[1].x = 1550;
	_poision[2].x = 1985;
	_poision[3].x = 2470;
	_poision[0].y = 1150;
	_poision[1].y = 1150;
	_poision[2].y = 1150;
	_poision[3].y = 1350;
	//��Ʈ
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
		//���� Ÿ��
		_poision[i].trap = TRAP_POISION;
	}//�������������൶ ������ ���Ϳ� ���ڡ�������������������
	for (int i = 0;i < 4;i++) { _vTrap.push_back(_poision[i]); }
	//���������������������� ��ġ ��Ʈ��������������������������������������������
	IMAGEMANAGER->addFrameImage("smallWater_Fall", "./image/ImageCollection/water_Fall.bmp", 588, 650, 4, 1, true, RGB(255, 0, 255));
	for (int i = 0; i < 3; i++)
	{
		_waterFall[i].frameX = 0;
		_waterFall[i].image = IMAGEMANAGER->findImage("smallWater_Fall");
	}
	//�����������������Ắ �� ���� ��ġ��������������������������������������������
	_isUpDown = false;
	IMAGEMANAGER->addImage("Stone_Door_5", "./image/ImageCollection/Stone_Door_5.bmp", 48, 243, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Stone_Door_4", "./image/ImageCollection/Stone_Door_4.bmp", 48, 192, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("BrownDoor_1", "./image/ImageCollection/BrownDoor.bmp", 45, 195, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("BrownDoor_2", "./image/ImageCollection/BrownDoor.bmp", 45, 195, false, RGB(0, 0, 0));
	_flyingBoard.image = IMAGEMANAGER->addImage("Moving_Flatform", "./image/ImageCollection/Moving_Flatform.bmp", 192, 45, false, RGB(0, 0, 0));
	_flyingBoard.rc = RectMake(1679, 325, 192, 45);
	//���� ��ǥ
	_flyingBoard.x = 1679;
	_flyingBoard.y = 325;
	//����Ÿ��
	_flyingBoard.trap = TRAP_BORAD;
	_breakableWallOne.rc = RectMake(1324, 225, 48, 243);
	_breakableWallTwo.rc = RectMake(3055, 85, 48, 192);
	_unbreakableWallOne.rc = RectMake(2090, 85, 45, 195);
	_unbreakableWallTwo.rc = RectMake(3695, 2055, 45, 195);
	//������������������� ���Ϳ� ���ڡ�������������������
	_vTrap.push_back(_flyingBoard);
	//����������������������� ��ġ��������������������������������������������
	_Items.oneBoom.image = IMAGEMANAGER->addImage("Boom", "./image/ImageCollection/Boom_Item.bmp", 48, 47, true, RGB(255, 0, 255));
	_Items.twoBoom.image = IMAGEMANAGER->addImage("Boom", "./image/ImageCollection/Boom_Item.bmp", 48, 47, true, RGB(255, 0, 255));
	_Items.oneTomato.image = IMAGEMANAGER->addImage("oneTomato", "./image/ImageCollection/item_hp2.bmp", 40, 48, true, RGB(255, 0, 255));
	_Items.twoTomato.image = IMAGEMANAGER->addImage("twoTomato", "./image/ImageCollection/item_hp2.bmp", 40, 48, true, RGB(255, 0, 255));
	_Items.blueKey.image = IMAGEMANAGER->addImage("BlueKey", "./image/ImageCollection/BlueKey.bmp", 27, 45, true, RGB(255, 0, 255));
	_Items.blueLocker.image = IMAGEMANAGER->addImage("BlueLocker", "./image/ImageCollection/BlueKey_Hole.bmp", 48, 48, false, RGB(0, 0, 0));
	_Items.redKey.image = IMAGEMANAGER->addImage("RedKey", "./image/ImageCollection/RedKey.bmp", 27, 54, true, RGB(255, 0, 255));
	_Items.redLocker.image = IMAGEMANAGER->addImage("RedLocker", "./image/ImageCollection/RedKey_Hole.bmp", 48, 48, false, RGB(0, 0, 0));
	//��ǥ
	_Items.oneBoom.x = 750;
	_Items.oneBoom.y = 60;
	_Items.twoBoom.x = 3600;
	_Items.twoBoom.y = 665;
	
	_Items.oneTomato.x = 1560;
	_Items.oneTomato.y = 155;
	_Items.twoTomato.x = 25;
	_Items.twoTomato.y = 640;
	
	_Items.blueKey.x = 2075;
	_Items.blueKey.y = 955;
	_Items.blueLocker.x = 3520;
	_Items.blueLocker.y = 2105;
	
	_Items.redKey.x = 1840;
	_Items.redKey.y = 555;
	_Items.redLocker.x = 2040;
	_Items.redLocker.y = 185;
	//��Ʈ
	_Items.oneBoom.rc = RectMake(750, 40, 40, 38);
	_Items.twoBoom.rc = RectMake(2790, 615, 40, 48);
	_Items.oneTomato.rc = RectMake(2790, 615, 40, 48);
	_Items.twoTomato.rc = RectMake(2790, 615, 40, 48);
	_Items.blueKey.rc = RectMake(2075, 955, 27, 45);
	_Items.blueLocker.rc = RectMake(3520, 2105, 48, 48);
	_Items.redKey.rc = RectMake(1840, 555, 27, 54);
	_Items.redLocker.rc = RectMake(2040, 185, 48, 48);
	//����
	_Items.oneBoom.item = ITEM_BOMB;
	_Items.twoBoom.item = ITEM_BOMB;
	_Items.oneTomato.item = ITEM_TOMATO;
	_Items.twoTomato.item = ITEM_TOMATO;
	_Items.blueKey.item = ITEM_BLUEKEY;
	_Items.blueLocker.item = ITEM_BLUELOCKER;
	_Items.redKey.item = ITEM_REDKEY;
	_Items.redLocker.item = ITEM_REDLOCKER;
	//��������������������� ���Ϳ� ���ڡ�������������������
	_vItem.push_back(_Items);
	//��������������������Ῡ����������������������������������������������
	_frameCount = 0;
	return S_OK;
}

void worldObjects::update()
{
	_frameCount++;
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
	//�����������������ᰡ�� ���� ��Ʈ��¡�������������������������������������������
	for (int i = 0; i < 3; i++)
	{
		if (KEYMANAGER->isStayKeyDown('Q'))
		{
			Rectangle(CAMERAMANAGER->getWorDC(), _niddle[i].rc);
		}
	}
	//���������������������� �̹��� ��¡�������������������������������������������
	IMAGEMANAGER->findImage("smallWater_Fall")->frameRender(CAMERAMANAGER->getWorDC(),
		1150, 132, _waterFall[0].frameX, _waterFall[0].frameY);
	//�����������������Ắ �� ���� �̹��� ��¡�������������������������������������������
	IMAGEMANAGER->findImage("Stone_Door_5")->render(CAMERAMANAGER->getWorDC(), _breakableWallOne.rc.left, _breakableWallOne.rc.top);
	IMAGEMANAGER->findImage("Stone_Door_4")->render(CAMERAMANAGER->getWorDC(), _breakableWallTwo.rc.left, _breakableWallTwo.rc.top);
	IMAGEMANAGER->findImage("BrownDoor_1")->render(CAMERAMANAGER->getWorDC(), _unbreakableWallOne.rc.left, _unbreakableWallOne.rc.top);
	IMAGEMANAGER->findImage("BrownDoor_2")->render(CAMERAMANAGER->getWorDC(), _unbreakableWallTwo.rc.left, _unbreakableWallTwo.rc.top);
	//IMAGEMANAGER->findImage("Moving_Flatform")->render(CAMERAMANAGER->getWorDC(), _flyingBoard.rc.left, _flyingBoard.rc.top);
	if (KEYMANAGER->isStayKeyDown('Q'))
	{//�����������������Ắ �浹 ��Ʈ ��¡�������������������������������������������
		Rectangle(CAMERAMANAGER->getWorDC(), _breakableWallOne.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _breakableWallTwo.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _unbreakableWallOne.rc);
		Rectangle(CAMERAMANAGER->getWorDC(), _unbreakableWallTwo.rc);
	}
	for (_viTrap = _vTrap.begin();_viTrap != _vTrap.end(); ++_viTrap)
	{
		if (_viTrap->trap == TRAP_POISION)
		{//�����������������ᵶ ���� �̹��� ��¡�������������������������������������������
			if (!_viTrap->isCollision)
			{
				if (KEYMANAGER->isStayKeyDown('Q'))
				{//�����������������ᵶ ���� ��Ʈ ��¡�������������������������������������������
					Rectangle(CAMERAMANAGER->getWorDC(), _viTrap->rc);
				}
				_viTrap->image->frameRender(CAMERAMANAGER->getWorDC(), _viTrap->x, _viTrap->y, _viTrap->frameX, _viTrap->frameY);
			}
		}//��������������������� �̹��� ��¡�������������������������������������������
		else if (_viTrap->trap == TRAP_BORAD)
		{
			_viTrap->image->render(CAMERAMANAGER->getWorDC(), _viTrap->x, _viTrap->y);
			if (KEYMANAGER->isStayKeyDown('Q'))
			{
				Rectangle(CAMERAMANAGER->getWorDC(), _viTrap->rc);
			}
		}
	}
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{//����������������������� �̹��� ��¡�������������������������������������������
		if (_viItem->oneBoom.item == ITEM_BOMB)
		{
			_viItem->oneBoom.image->render(CAMERAMANAGER->getWorDC(), _viItem->oneBoom.x, _viItem->oneBoom.y);
		}
		if (_viItem->twoBoom.item == ITEM_BOMB)
		{
			_viItem->twoBoom.image->render(CAMERAMANAGER->getWorDC(), _viItem->twoBoom.x, _viItem->twoBoom.y);
		}
		if (_viItem->oneTomato.item == ITEM_TOMATO)
		{
			_viItem->oneTomato.image->render(CAMERAMANAGER->getWorDC(), _viItem->oneTomato.x, _viItem->oneTomato.y);
		}
		if (_viItem->twoTomato.item == ITEM_TOMATO)
		{
			_viItem->twoTomato.image->render(CAMERAMANAGER->getWorDC(), _viItem->twoTomato.x, _viItem->twoTomato.y);
		}
		if (_viItem->blueKey.item == ITEM_BLUEKEY)
		{
			_viItem->blueKey.image->render(CAMERAMANAGER->getWorDC(), _viItem->blueKey.x, _viItem->blueKey.y);
		}
		if (_viItem->blueLocker.item == ITEM_BLUELOCKER)
		{
			_viItem->blueLocker.image->render(CAMERAMANAGER->getWorDC(), _viItem->blueLocker.x, _viItem->blueLocker.y);
		}
		if (_viItem->redKey.item == ITEM_REDKEY)
		{
			_viItem->redKey.image->render(CAMERAMANAGER->getWorDC(), _viItem->redKey.x, _viItem->redKey.y);
		}
		if (_viItem->redLocker.item == ITEM_REDLOCKER)
		{
			_viItem->redLocker.image->render(CAMERAMANAGER->getWorDC(), _viItem->redLocker.x, _viItem->redLocker.y);
		}
	}
}

void worldObjects::framework()
{
	RECT temp;
	for (_viTrap = _vTrap.begin();_viTrap != _vTrap.end(); ++_viTrap)
	{
		if (_frameCount % 2 == 0)
		{
			if (_viTrap->trap == TRAP_POISION)
			{//�����������������ᵶ�� ���ÿ� �浹���� �ʾҴٸ� �����ӡ�������������������������������������������
				if (!IntersectRect(&temp, &_viTrap->rc, &_niddle[1].rc))
				{
					_viTrap->image->setFrameX(_viTrap->frameX);
					if (_viTrap->frameX >= 0) {	_viTrap->frameX = 0;}
				}//�����������������ᵶ�� ���ÿ� �浹�ߴٸ� �����ӡ�������������������������������������������
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
	//���������������������� �����ӡ�������������������������������������������
	if (_frameCount % 3 == 0)
	{
		_waterFall[0].image->setFrameX(_waterFall[0].frameX);
		_waterFall[0].frameX++;
		if (_waterFall[0].frameX > _waterFall[0].image->getMaxFrameX()) { _waterFall[0].frameX = 0; }
	}
}

void worldObjects::move()
{
	RECT temp;
	for (_viTrap = _vTrap.begin();_viTrap != _vTrap.end(); ++_viTrap)
	{
		if (_viTrap->trap == TRAP_POISION)
		{//�����������������ᵶ ���� �����ӡ�������������������������������������������
			if (!IntersectRect(&temp, &_viTrap->rc, &_niddle[1].rc))
			{
				_viTrap->y += 5;
			}
		}
		else if (_viTrap->trap == TRAP_BORAD)
		{//��������������������� �����ӡ�������������������������������������������
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
}