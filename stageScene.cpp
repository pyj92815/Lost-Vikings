#include "stdafx.h"
#include "stageScene.h"


stageScene::stageScene()
{
	addStageImage();	// 이미지 추가 함수
}


stageScene::~stageScene()
{
}

HRESULT stageScene::init()
{
	_wm = new worldMap;
	_wm->init();

	_pm = new playerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	posSetting();	// UI의 좌표를 설정한다. (캐릭터 상태 + 인벤토리)

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	_wm->update();
	_pm->update();
	_em->update();

	testStateImage();  // 캐릭터 전환 테스트
}

void stageScene::render()
{
	// 테스트용 배경이다. 이후에는 지울것!
	//IMAGEMANAGER->findImage("Test_BG")->render(getMemDC(), 0, 0);

	//CAMERAMANAGER->get_WorImage()->render(getMemDC(), 0, 0);
	_wm->render();
	_pm->render();
	_em->render();

	CAMERAMANAGER->get_WorImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(),
		CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

	//IMAGEMANAGER->findImage("OBJECT")->render(getMemDC(), 0, 0, CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(),
		//CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

	IMAGEMANAGER->findImage("UI_Image")->render(getMemDC(), 0, WINSIZEY - (WINSIZEY - 573));

	// 쓰레기통 출력
	_UI_Garbage.image->render(getMemDC(), _UI_Garbage.rc.left, _UI_Garbage.rc.top);

	// 테스트용 렉트
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(getMemDC(), _UI_State[i].rc);
		_UI_State[i].image->frameRender(getMemDC(), _UI_State[i].rc.left, _UI_State[i].rc.top,
			_UI_State[i].image->getFrameX(), 0);
	}


}

void stageScene::posSetting()
{
	// 상태 UI 초기화
	_UI_State[PT_Run].image = new image;
	_UI_State[PT_Run].image = IMAGEMANAGER->findImage("R_State");

	_UI_State[PT_Attack].image = new image;
	_UI_State[PT_Attack].image = IMAGEMANAGER->findImage("A_State");

	_UI_State[PT_Def].image = new image;
	_UI_State[PT_Def].image = IMAGEMANAGER->findImage("S_State");


	_UI_State[PT_Run].pos.x = 185;
	_UI_State[PT_Run].pos.y = WINSIZEY - 95;

	_UI_State[PT_Attack].pos.x = 400;
	_UI_State[PT_Attack].pos.y = WINSIZEY - 95;

	_UI_State[PT_Def].pos.x = 615;
	_UI_State[PT_Def].pos.y = WINSIZEY - 95;

	_UI_State[PT_Run].rc = RectMakeCenter(_UI_State[PT_Run].pos.x, _UI_State[PT_Run].pos.y,
		_UI_State[PT_Run].image->getFrameWidth(), _UI_State[PT_Run].image->getFrameHeight());
	_UI_State[PT_Run].rc.left += 2;	// 삐져나온 위치 조정
	_UI_State[PT_Run].rc.right += 2;
	_UI_State[PT_Run].rc.top -= 2;
	_UI_State[PT_Run].rc.bottom -= 2;

	_UI_State[PT_Attack].rc = RectMakeCenter(_UI_State[PT_Attack].pos.x, _UI_State[PT_Attack].pos.y,
		_UI_State[PT_Attack].image->getFrameWidth(), _UI_State[PT_Attack].image->getFrameHeight());
	_UI_State[PT_Attack].rc.top -= 2;
	_UI_State[PT_Attack].rc.bottom -= 2;

	_UI_State[PT_Def].rc = RectMakeCenter(_UI_State[PT_Def].pos.x, _UI_State[PT_Def].pos.y,
		_UI_State[PT_Def].image->getFrameWidth(), _UI_State[PT_Def].image->getFrameHeight());
	_UI_State[PT_Def].rc.top -= 2;
	_UI_State[PT_Def].rc.bottom -= 2;

	// 시작 시엔 빨간놈이 선택되어 있다
	_UI_State[PT_Run].image->setFrameX(1);


	// 인벤토리 UI 초기화 (캐릭터마다 4개씩 있다.)
	

	// 쓰레기통 UI 초기화
	_UI_Garbage.image = IMAGEMANAGER->findImage("GarbageBox");
	_UI_Garbage.rc = RectMake(764, _UI_State[PT_Run].rc.top, _UI_Garbage.image->getWidth(), _UI_Garbage.image->getHeight());
	_UI_Garbage.pos.x = (_UI_Garbage.rc.left + _UI_Garbage.rc.right) / 2;
	_UI_Garbage.pos.y = (_UI_Garbage.rc.top + _UI_Garbage.rc.bottom) / 2;

	// 캐릭터 전환 변수 (이 숫자가 바뀌면 그 캐릭터를 바라본다?)  
	_charNum = PT_Run;

}

void stageScene::addStageImage()
{
	// 스테이지 UI에서 사용할 이미지를 저장한다.
	IMAGEMANAGER->addImage("Test_BG", "./image/UI/UI_Inventory/Test_BG.bmp", 960, 573, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("A_State", "./image/UI/UI_Inventory/A_Player_Image.bmp", 305, 80, 3, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("R_State", "./image/UI/UI_Inventory/R_Player_Image.bmp", 305, 80, 3, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("S_State", "./image/UI/UI_Inventory/S_Player_Image.bmp", 305, 80, 3, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Life_Image", "./image/UI/UI_Inventory/Life_Point.bmp", 12, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GarbageBox", "./image/UI/UI_Inventory/Garbage_Box.bmp", 46, 47, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Select_Image", "./image/UI/UI_Inventory/Select_Point.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Image", "./image/UI/UI_Inventory/UI_Image.bmp", 960, 185, true, RGB(255, 0, 255));
}

void stageScene::testStateImage()
{

	// 테스트용 컨트롤을 누른다면
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		//_UI_State[_charNum].image->setFrameX(0);
		//_charNum++;
		//if (_charNum > PT_Def) _charNum = PT_Run;
		//_UI_State[_charNum].image->setFrameX(1);

		_UI_State[_charNum].image->setFrameX(0);	// 캐릭터가 교체되면 기존에 있던 캐릭터는 0의 이미지로 수정
		_charNum++;									// 다음 캐릭터를 위해 숫자를 증가시켜준다.
		if (_charNum == 3)	_charNum = 0;			// 만약 캐릭터의 수보다 넘어가면
		if (_UI_State[_charNum].dead)
		{
			_charNum++;								// 만약 다음 캐릭터가 죽어있다면, 다음 캐릭터를 조회한다.
			if (_charNum == 3)	_charNum = 0;			// 만약 캐릭터의 수보다 넘어가면

			if (_UI_State[_charNum].dead)
				_charNum++;
			if (_charNum == 3)	_charNum = 0;			// 만약 캐릭터의 수보다 넘어가면
		}
		_UI_State[_charNum].image->setFrameX(1);

		// 상황에 맞게 카메라 좌표를 넘겨줘야한다.
		// 만약 캐릭터가 아니라면 0의 이미지를 출력해주도록 바꿔준다.
		// 캐릭터가 선택되어 있는 상황이라면 1의 이미지를 출력한다.

	}

	_pm->set_Playing(_charNum);

	switch (_charNum)
	{
		case 0:
			CAMERAMANAGER->set_Camera_XY(_pm->getPlayerEric().x, _pm->getPlayerEric().y);
			break;

		case 1:
			CAMERAMANAGER->set_Camera_XY(_pm->getPlayerBaleog().x, _pm->getPlayerBaleog().y);
			break;

		case 2:
			CAMERAMANAGER->set_Camera_XY(_pm->getPlayerOlaf().x, _pm->getPlayerOlaf().y);
			break;
	}
	

	set_PlayerDead();
}

void stageScene::set_PlayerDead()
{
	// 캐릭터의 생존 유무를 받아서 저장한다.
	// 만약 캐릭터가 죽었다면 상태 이미지는 죽어있게 한다.
	_UI_State[PT_Run].dead = _pm->getPlayerEric().isDead;
	_UI_State[PT_Attack].dead = _pm->getPlayerBaleog().isDead;
	_UI_State[PT_Def].dead = _pm->getPlayerOlaf().isDead;

	// 만약 dead값이 true면 캐릭터가 죽었다는 뜻
	if (_UI_State[PT_Run].dead)
	{
		_UI_State[PT_Run].image->setFrameX(2);		// 이미지는 죽은 이미지로 교체한다.
	}

	if (_UI_State[PT_Attack].dead)
	{
		_UI_State[PT_Attack].image->setFrameX(2);	// 이미지는 죽은 이미지로 교체한다.
	}

	if (_UI_State[PT_Def].dead)
	{
		_UI_State[PT_Def].image->setFrameX(2);		// 이미지는 죽은 이미지로 교체한다.
	}

	// 만약 캐릭터가 죽었을 경우에 다음 캐릭터로 바꾸는 기능
	if (_UI_State[_charNum].dead)
	{
		while (true)
		{
			// 캐릭터가 모두 죽은 상황은 게임 오버 화면으로 넘어간다.
			if (_UI_State[PT_Run].dead && _UI_State[PT_Attack].dead && _UI_State[PT_Def].dead)
			{
				// 인터벌을 주고 넘어갈지 그냥 넘어갈지 정하고
				// 게임 오버 씬으로 넘어간다.
				// 임시로 인트로 씬으로 넘겼음
				_wm->init();
				_pm->init();
				_em->init();
				SCENEMANAGER->set_SceneState(SS_INTRO);
				break;
			}

			_charNum++;

			if (!_UI_State[_charNum].dead)
			{
				_UI_State[_charNum].image->setFrameX(1);	// 캐릭터가 살이있으니까 캐릭터를 켜준다.
				break;										// 만약 다음 캐릭터가 죽지 않았다면 와일문 나가기
			}

			if (_charNum == 3)	_charNum = 0;				// 만약 캐릭터의 개수를 초과했다면 다시 0번으로
		}
	}
}
