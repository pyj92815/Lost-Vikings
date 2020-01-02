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

	// 191229 PM 02:56 월드 좌표와 카메라의 크기를 셋팅해준다. + 월드 DC
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
	// 191229 PM 02:09 보여지는 부분 카메라 좌표를 수정했음 -형길-
	// 191229 PM 19:11 -락훈 - 렉 때문에 blackground를 지우고 patBlt로 카메라 배경만큼 그리도록 함 

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
