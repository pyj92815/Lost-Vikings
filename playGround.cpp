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

	_enemyManager = new EnemyManager;
	_enemyManager->init();
	
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

	_enemyManager->update();

	if(SCENEMANAGER->get_SceneState() == SS_STAGE)	_pm->update();

}

//����� �׷���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::render()
{
	PatBlt(CAMERAMANAGER->getWorDC(), 0, 0, CAMERAMANAGER->get_WorldSize_X(), CAMERAMANAGER->get_WorldSize_Y(), WHITENESS);
	//==================================================
	_wd->render();

	_pm->render();


	// 191229 PM 19:11 -���� - WorldDc �ɸ���-> PG�� �������κ� �ű� 

	_enemyManager->render();

	_sm->render();
	
	//===================================================
	//�� ���ߴ�
	_backBuffer->render(getHDC(), 0, 0);
}
