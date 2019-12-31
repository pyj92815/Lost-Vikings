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

	if (SCENEMANAGER->get_SceneState() == SS_STAGE)
	{
		_enemyManager->update();
		_pm->update();
	}

}

//여기다 그려라!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!대훈아 어제 뭐 했길레 오자마자 잠이드는 거니?
void playGround::render()
{
	PatBlt(CAMERAMANAGER->getWorDC(), 0, 0, CAMERAMANAGER->get_WorldSize_X(), CAMERAMANAGER->get_WorldSize_Y(), WHITENESS);
	//==================================================
	
	_wd->render();

	_pm->render();

<<<<<<< HEAD

	// 191229 PM 19:11 -락훈 - WorldDc 케릭터-> PG로 렌더링부분 옮김 

=======
>>>>>>> 6404d0946eda9d809087c9b2912bb539d8601016
	_enemyManager->render();

	_sm->render();
<<<<<<< HEAD
	TIMEMANAGER->render(getMemDC());
=======

	
>>>>>>> 321e694003ebbbef6a52f8696155feb7550821dd
	//===================================================
	//딱 말했다
	_backBuffer->render(getHDC(), 0, 0);
}
