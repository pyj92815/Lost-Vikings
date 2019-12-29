#pragma once
#include "singletonBase.h"

// �÷��̾� Ŭ���� ���� ����?

struct _tagCamera
{
	POINTFLOAT world_Size, cameraXY;		// ���� ������, ī�޶� ��ǥ�� ������
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

	void set_WorldSize(string strKey);							// ���� ����� �޾ƿ´�.
	float get_WorldSize_X() { return _camera.world_Size.x; }	// ���� ������ X�� ȣ���Ѵ�.
	float get_WorldSize_Y() { return _camera.world_Size.y; }	// ���� ������ Y�� ȣ���Ѵ�.

	void set_CameraSize(int x, int y) { _camera.cameraSizeX = x; _camera.cameraSizeY = y; };
	int get_CameraSizeX() { return _camera.cameraSizeX; }
	int get_CameraSizeY() { return _camera.cameraSizeY; }

	void set_Camera_XY(int x, int y);							// ĳ������ ��ǥ�� �ʱ�ȭ�Ѵ�.
	void set_Camera_XY(float x, float y);						// ĳ������ ��ǥ�� �ʱ�ȭ�Ѵ�.
	void set_Camera_XY(POINT xy);								// ĳ������ ��ǥ�� �ʱ�ȭ�Ѵ�.
	void set_Camera_XY(POINTFLOAT xy);							// ĳ������ ��ǥ�� �ʱ�ȭ�Ѵ�.
	void set_Camera_XY(RECT rc);								// ĳ������ ��ǥ�� �ʱ�ȭ�Ѵ�.

	float get_Camera_X() { return _camera.cameraXY.x; }			// ī�޶� X��ǥ�� �����´�.
	float get_Camera_Y() { return _camera.cameraXY.y; }			// ī�޶� y��ǥ�� �����´�.

	void Camera_Correction();									// ī�޶� ����ó�� �Լ�
};

