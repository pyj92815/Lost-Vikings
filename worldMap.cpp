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
<<<<<<< HEAD
//	PatBlt(CAMERAMANAGER->getWorDC(), CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), WINSIZEX, WINSIZEY, BLACKNESS);
<<<<<<< HEAD
	IMAGEMANAGER->findImage("Background")->render(CAMERAMANAGER->getWorDC(), 0, 0);
	_wo->render();
	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		IMAGEMANAGER->findImage("BG")->render(CAMERAMANAGER->getWorDC(), 0, 0);
	}
=======
=======
	//PatBlt(CAMERAMANAGER->getWorDC(), CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), WINSIZEX, WINSIZEY, BLACKNESS);
>>>>>>> 6404d0946eda9d809087c9b2912bb539d8601016
	IMAGEMANAGER->findImage("BG")->render(CAMERAMANAGER->getWorDC(), 0, 0);
>>>>>>> 321e694003ebbbef6a52f8696155feb7550821dd
	//IMAGEMANAGER->findImage("OBJECT")->render(CAMERAMANAGER->getWorOBDC(), 0, 0);
	//worldImage->render(getMemDC(), 0, 0,
	//	CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());


}
