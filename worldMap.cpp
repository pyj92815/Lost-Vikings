#include "stdafx.h"
#include "worldMap.h"


worldMap::worldMap()
{
}


worldMap::~worldMap()
{
}

HRESULT worldMap::init()
{
	IMAGEMANAGER->addImage("BG", "./image/map/secondTest.bmp", 3840, 2292, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Background", "./image/map/blackground.bmp", 3840, 2292, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("OBJECT", "./image/Map/first.bmp", 3840, 2292, true, RGB(255, 0, 255));

	// 191229 PM 02:56 ���� ��ǥ�� ī�޶��� ũ�⸦ �������ش�. + ���� DC
	CAMERAMANAGER->set_WorldSize("BG");
	CAMERAMANAGER->set_CameraSize(960, 573);

	_wo = new worldObjects;
	_wo->init();

	return S_OK;
}

void worldMap::release()
{
}

void worldMap::update()
{
	_wo->update();
}

void worldMap::render()
{
	// 191229 PM 02:09 �������� �κ� ī�޶� ��ǥ�� �������� -����-
	// 191229 PM 19:11 -���� - �� ������ blackground�� ����� patBlt�� ī�޶� ��游ŭ �׸����� �� 

//	PatBlt(CAMERAMANAGER->getWorDC(), CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), WINSIZEX, WINSIZEY, BLACKNESS);



//	PatBlt(CAMERAMANAGER->getWorDC(), CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), WINSIZEX, WINSIZEY, BLACKNESS);

	IMAGEMANAGER->findImage("Background")->render(CAMERAMANAGER->getWorDC(), 0, 0);
	_wo->render();
	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		IMAGEMANAGER->findImage("BG")->render(CAMERAMANAGER->getWorDC(), 0, 0);
	}


	IMAGEMANAGER->findImage("BG")->render(CAMERAMANAGER->getWorDC(), 0, 0);

}
