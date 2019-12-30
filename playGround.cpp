#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

//메모리 해제는 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::release()
{
	gameNode::release();

	
}

//연산은 여기다 해라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::update()
{
	gameNode::update();
	_wd->update();

	_sm->update();
	_enemyManager->update();

	if(SCENEMANAGER->get_SceneState() == SS_STAGE)	_pm->update();

}

//여기다 그려라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void playGround::render()
{
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================
	_wd->render();

	_pm->render();

<<<<<<< HEAD

	// 191229 PM 19:11 -락훈 - WorldDc 케릭터-> PG로 렌더링부분 옮김 
	CAMERAMANAGER->getWorImage()->render(getMemDC(), 0, 0,
		CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y()
		, CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

	_enemyManager->render();

=======
>>>>>>> 7c6969c42fefc7480e17ee67445ad5bcd63b637b
	_sm->render();
	
	//===================================================
	//딱 말했다
	_backBuffer->render(getHDC(), 0, 0);
}
