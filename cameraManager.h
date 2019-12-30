#pragma once
#include "singletonBase.h"

// 플레이어 클래스 전방 선언?

struct _tagCamera
{
	POINTFLOAT world_Size, cameraXY;		// 월드 사이즈, 카메라 좌표를 담을곳
	int		   cameraSizeX, cameraSizeY;	// 카메라의 사이즈
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	_tagCamera  _camera;

	HDC			_worldDC;  // 플레이어, 적, 함정, 아이템을 그려줄 DC
	image*		_worImage;

	HDC			_worldObjectDC;	// 배경 오브젝트를 그려줄 DC
	image*		_worObImage;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 월드 사이즈
	void  set_WorldSize(string strKey);							// 월드 사이즈를 세팅한다.
	float get_WorldSize_X() { return _camera.world_Size.x; }	// 월드 사이즈 X를 가져온다.
	float get_WorldSize_Y() { return _camera.world_Size.y; }	// 월드 사이즈 Y를 가져온다.

	// 카메라 사이즈
	void set_CameraSize(int x, int y) { _camera.cameraSizeX = x; _camera.cameraSizeY = y; };	// 카메라의 사이즈를 세팅한다.
	int  get_CameraSizeX() { return _camera.cameraSizeX; }										// 카메라 사이즈 x를 가져온다.
	int  get_CameraSizeY() { return _camera.cameraSizeY; }										// 카메라 사이즈 y를 가져온다.

	// 카메라의 xy 좌표
	void set_Camera_XY(int x, int y);							// 캐릭터의 좌표를 세팅한다.
	void set_Camera_XY(float x, float y);						// 캐릭터의 좌표를 세팅한다.
	void set_Camera_XY(POINT xy);								// 캐릭터의 좌표를 세팅한다.
	void set_Camera_XY(POINTFLOAT xy);							// 캐릭터의 좌표를 세팅한다.
	void set_Camera_XY(RECT rc);								// 캐릭터의 좌표를 세팅한다.

	float get_Camera_X() { return _camera.cameraXY.x; }			// 카메라 X좌표를 가져온다.
	float get_Camera_Y() { return _camera.cameraXY.y; }			// 카메라 y좌표를 가져온다.

	// 카메라가 맵 밖으로 나가지 못하게
	void Camera_Correction();									// 카메라 예외처리 함수

	// 월드 DC
	HDC  getWorDC() { return _worldDC; }						// _worldDC를 가져온다.
	image* get_WorImage() { return _worImage; }

	// 월드 오브젝트 DC
	HDC getWorOBDC() { return _worldObjectDC; }
	image* get_worObImage() { return _worObImage; }
};

