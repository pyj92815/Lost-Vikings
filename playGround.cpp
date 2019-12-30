#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ض�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	_wd = new worldMap;
	_wd->init();

	_sm = new scene_Manager;
	_sm->init();

	_pm = new playerManager;
	_pm->init();

	
	return S_OK;
}

//�޸� ������ ����� �ض�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::release()
{
	gameNode::release();

	
}

//������ ����� �ض�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::update()
{
	gameNode::update();
	_wd->update();

	_sm->update();

	if(SCENEMANAGER->get_SceneState() == SS_STAGE)	_pm->update();

}

//����� �׷���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================
	_wd->render();

	_pm->render();

<<<<<<< HEAD
	// 191229 PM 19:11 -���� - WorldDc �ɸ���-> PG�� �������κ� �ű� 
	CAMERAMANAGER->getWorImage()->render(getMemDC(), 0, 0,
		CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y()
		, CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
=======
	_sm->render();
	
>>>>>>> 0a98c4f5ba4f76f6ae71ea8b9fd4a32109aa1889
	//===================================================
	//�� ���ߴ�
	_backBuffer->render(getHDC(), 0, 0);
}
