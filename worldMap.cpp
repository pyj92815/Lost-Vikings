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
	IMAGEMANAGER->addImage("firstground", "./image/Map/first.bmp", 3840, 2292, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackground", "./image/Map/blackground.bmp", 3840, 2292, false, RGB(0, 0, 0));

	worldImage = new image;
	worldImage = IMAGEMANAGER->addImage("worldMap", 3840, 2292);
	worldDC = worldImage->getMemDC();

	// 191229 PM 02:56 ���� ��ǥ�� ī�޶��� ũ�⸦ �������ش�. + ���� DC
	CAMERAMANAGER->set_WorldSize("background");
	CAMERAMANAGER->set_CameraSize(960, 573);
	CAMERAMANAGER->set_worldDC(worldDC);
	
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
	// 191229 PM 19:11 -���� - �� ������ blackground�� ����� patBlt�� ī�޶� ��游ŭ �׸����� �� 
	PatBlt(CAMERAMANAGER->getWorDC(), CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(CAMERAMANAGER->getWorDC(), 0, 0, 3840, 2292, BLACKNESS);  => ���ɸ�
	//IMAGEMANAGER->findImage("blackground")->render(CAMERAMANAGER->getWorDC(), 0, 0); => ���ɸ� 
	IMAGEMANAGER->findImage("background")->render(CAMERAMANAGER->getWorDC(), 0, 0);
	IMAGEMANAGER->findImage("firstground")->render(CAMERAMANAGER->getWorDC(), 0, 0);
	CAMERAMANAGER->setWorImage(worldImage); //?
	//worldImage->render(getMemDC(), 0, 0,
	//	CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

}
