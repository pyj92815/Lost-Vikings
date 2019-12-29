#pragma once
#include "singletonBase.h"

// 플레이어 클래스 전방 선언?

struct _tagCamera
{
	POINTFLOAT world_Size, cameraXY;		// 월드 사이즈, 카메라 좌표를 담을곳
	int		   cameraSizeX, cameraSizeY;
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	_tagCamera  _camera;

	HDC			_worldDC;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void set_WorldSize(string strKey);							// 월드 사이즈를 받아온다.
	float get_WorldSize_X() { return _camera.world_Size.x; }	// 월드 사이즈 X를 호출한다.
	float get_WorldSize_Y() { return _camera.world_Size.y; }	// 월드 사이즈 Y를 호출한다.

	void set_CameraSize(int x, int y) { _camera.cameraSizeX = x; _camera.cameraSizeY = y; };
	int get_CameraSizeX() { return _camera.cameraSizeX; }
	int get_CameraSizeY() { return _camera.cameraSizeY; }

	void set_Camera_XY(int x, int y);							// 캐릭터의 좌표를 초기화한다.
	void set_Camera_XY(float x, float y);						// 캐릭터의 좌표를 초기화한다.
	void set_Camera_XY(POINT xy);								// 캐릭터의 좌표를 초기화한다.
	void set_Camera_XY(POINTFLOAT xy);							// 캐릭터의 좌표를 초기화한다.
	void set_Camera_XY(RECT rc);								// 캐릭터의 좌표를 초기화한다.

	float get_Camera_X() { return _camera.cameraXY.x; }			// 카메라 X좌표를 가져온다.
	float get_Camera_Y() { return _camera.cameraXY.y; }			// 카메라 y좌표를 가져온다.

	void Camera_Correction();									// 카메라 예외처리 함수
};

