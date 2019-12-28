#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{
}

void cameraManager::render()
{
}

void cameraManager::set_WorldSize(string strKey)
{
	_camera.world_Size.x = IMAGEMANAGER->findImage(strKey)->getWidth();
	_camera.world_Size.y = IMAGEMANAGER->findImage(strKey)->getHeight();
}


void cameraManager::set_Camera_XY(int x, int y)
{
	_camera.cameraXY.x = WINSIZEX / 2 - x;
	_camera.cameraXY.y = WINSIZEY / 2 - y;
}

void cameraManager::set_Camera_XY(float x, float y)
{
	_camera.cameraXY.x = WINSIZEX / 2 - x;
	_camera.cameraXY.y = WINSIZEY / 2 - y;
}

void cameraManager::set_Camera_XY(POINT xy)
{
	_camera.cameraXY.x = WINSIZEX / 2 - xy.x;
	_camera.cameraXY.y = WINSIZEY / 2 - xy.y;
}

void cameraManager::set_Camera_XY(POINTFLOAT xy)
{
	_camera.cameraXY.x = WINSIZEX / 2 - xy.x;
	_camera.cameraXY.y = WINSIZEY / 2 - xy.y;
}

void cameraManager::set_Camera_XY(RECT rc)
{
	_camera.cameraXY.x = WINSIZEX / 2 - (rc.right - rc.left);
	_camera.cameraXY.y = WINSIZEY / 2 - (rc.bottom - rc.top);
}
