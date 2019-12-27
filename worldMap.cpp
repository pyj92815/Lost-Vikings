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
	IMAGEMANAGER->findImage("background")->render(worldDC,0,0);
	worldImage->render(getMemDC(), 0, 0, 0 , 0, 960, 573);


}
