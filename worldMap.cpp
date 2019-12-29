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
	IMAGEMANAGER->addImage("background", "./image/map/secondTest.bmp", 3840, 2292, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("character", "./image/ImageCollection/Viking_Eric.bmp", 80, 100, true, RGB(255, 0, 255));

	worldImage = new image;
	worldImage = IMAGEMANAGER->addImage("worldMap", 3840, 2292);
	worldDC = worldImage->getMemDC();

	// 191229 PM 02:56 ���� ��ǥ�� ī�޶��� ũ�⸦ �������ش�.
	CAMERAMANAGER->set_WorldSize("background");
	CAMERAMANAGER->set_CameraSize(960, 573);

	return S_OK;
}

void worldMap::release()
{
}

void worldMap::update()
{
}

void worldMap::render()
{
	// 191229 PM 02:09 �������� �κ� ī�޶� ��ǥ�� �������� -����-
	IMAGEMANAGER->findImage("background")->render(worldDC, 0, 0);
	worldImage->render(getMemDC(), 0, 0,
		CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());


}
