#pragma once
#include "singletonBase.h"

// �÷��̾� Ŭ���� ���� ����?

struct _tagCamera
{
	POINTFLOAT world_Size, cameraXY;		// ���� ������, ī�޶� ��ǥ�� ������
	int		   cameraSizeX, cameraSizeY;	// ī�޶��� ������
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	_tagCamera  _camera;

	HDC			_worldDC;
	image*		__worImage;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// ���� ������
	void  set_WorldSize(string strKey);							// ���� ����� �����Ѵ�.
	float get_WorldSize_X() { return _camera.world_Size.x; }	// ���� ������ X�� �����´�.
	float get_WorldSize_Y() { return _camera.world_Size.y; }	// ���� ������ Y�� �����´�.

	// ī�޶� ������
	void set_CameraSize(int x, int y) { _camera.cameraSizeX = x; _camera.cameraSizeY = y; };	// ī�޶��� ����� �����Ѵ�.
	int  get_CameraSizeX() { return _camera.cameraSizeX; }										// ī�޶� ������ x�� �����´�.
	int  get_CameraSizeY() { return _camera.cameraSizeY; }										// ī�޶� ������ y�� �����´�.

	// ī�޶��� xy ��ǥ
	void set_Camera_XY(int x, int y);							// ĳ������ ��ǥ�� �����Ѵ�.
	void set_Camera_XY(float x, float y);						// ĳ������ ��ǥ�� �����Ѵ�.
	void set_Camera_XY(POINT xy);								// ĳ������ ��ǥ�� �����Ѵ�.
	void set_Camera_XY(POINTFLOAT xy);							// ĳ������ ��ǥ�� �����Ѵ�.
	void set_Camera_XY(RECT rc);								// ĳ������ ��ǥ�� �����Ѵ�.

	float get_Camera_X() { return _camera.cameraXY.x; }			// ī�޶� X��ǥ�� �����´�.
	float get_Camera_Y() { return _camera.cameraXY.y; }			// ī�޶� y��ǥ�� �����´�.

	// ī�޶� �� ������ ������ ���ϰ�
	void Camera_Correction();									// ī�޶� ����ó�� �Լ�


	// ����DC, ����Img ����
	void set_worldDC(HDC wDC) { _worldDC = wDC; }				// _worldDC�� �����Ѵ�.
	HDC  getWorDC() { return _worldDC; }						// _worldDC�� �����´�.

	void setWorImage(image* img) { __worImage = img; }
	image* getWorImage() { return __worImage; }

};
