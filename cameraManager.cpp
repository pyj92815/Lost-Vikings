#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
	_camera.cameraSizeX =   NULL;
	_camera.cameraSizeY =   NULL;
	_camera.cameraXY.x =    NULL;
	_camera.cameraXY.y =    NULL;
	_camera.world_Size.x =  NULL;
	_camera.world_Size.y =  NULL;
	_worldDC =				NULL;
	__worImage =			NULL;
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
	_camera.cameraXY.x = x - _camera.cameraSizeX / 2.f;
	_camera.cameraXY.y = y - _camera.cameraSizeX / 2.f;

	Camera_Correction();	// 카메라가 맵 밖으로 나갔을때 예외처리
}

void cameraManager::set_Camera_XY(float x, float y)
{
	_camera.cameraXY.x = x - _camera.cameraSizeX / 2.f;
	_camera.cameraXY.y = y - _camera.cameraSizeX / 2.f;

	Camera_Correction();	// 카메라가 맵 밖으로 나갔을때 예외처리
}

void cameraManager::set_Camera_XY(POINT xy)
{
	_camera.cameraXY.x = xy.x - _camera.cameraSizeX / 2.f;
	_camera.cameraXY.y = xy.y - _camera.cameraSizeX / 2.f;

	Camera_Correction();	// 카메라가 맵 밖으로 나갔을때 예외처리
}

void cameraManager::set_Camera_XY(POINTFLOAT xy)
{
	_camera.cameraXY.x = xy.x - _camera.cameraSizeX / 2.f;
	_camera.cameraXY.y = xy.y - _camera.cameraSizeX / 2.f;

	Camera_Correction();	// 카메라가 맵 밖으로 나갔을때 예외처리
}

void cameraManager::set_Camera_XY(RECT rc)
{
	// 받아온 rc의 x, y 중심좌표를 구해서, 카메라 사이즈 절반 만큼을 빼주면
	// 카메라의 left, top 좌표가 구해진다.
	_camera.cameraXY.x = ((rc.right + rc.left) / 2) - _camera.cameraSizeX / 2;
	_camera.cameraXY.y = ((rc.bottom + rc.top) / 2) - _camera.cameraSizeY / 2;

	Camera_Correction();	// 카메라가 맵 밖으로 나갔을때 예외처리
}

void cameraManager::Camera_Correction()
{
	// 만약 카메라가 맵을 넘어가려고 할때 보정을 해준다.
	if (_camera.cameraXY.x < 0) _camera.cameraXY.x = 0;
	if (_camera.cameraXY.y < 0) _camera.cameraXY.y = 0;
	if (_camera.cameraXY.x + _camera.cameraSizeX > _camera.world_Size.x)
		_camera.cameraXY.x = _camera.world_Size.x - _camera.cameraSizeX;
	if (_camera.cameraXY.y + _camera.cameraSizeY > _camera.world_Size.y)
		_camera.cameraXY.y = _camera.world_Size.y - _camera.cameraSizeY;
}
