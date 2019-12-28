#pragma once
#include "gameNode.h"

// �÷��̾� Ŭ���� ���� ����?

struct _tagCamera
{
	POINTFLOAT world_Size, cameraXY;		// ���� ������, ī�޶� ��ǥ�� ������

};

class cameraManager : public gameNode
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

	void set_Camera_XY(int x, int y);							// ĳ������ ��ǥ�� �����´�.
	void set_Camera_XY(float x, float y);						// ĳ������ ��ǥ�� �����´�.
	void set_Camera_XY(POINT xy);								// ĳ������ ��ǥ�� �����´�.
	void set_Camera_XY(POINTFLOAT xy);							// ĳ������ ��ǥ�� �����´�.
	void set_Camera_XY(RECT rc);								// ĳ������ ��ǥ�� �����´�.

};

