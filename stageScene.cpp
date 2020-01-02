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


	IMAGEMANAGER->findImage("OBJECT")->render(getMemDC(), 0, 0, CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(),
		CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

	IMAGEMANAGER->findImage("UI_Image")->render(getMemDC(), 0, WINSIZEY - (WINSIZEY - 573));

	// 쓰레기통 출력
	_UI_Garbage.image->render(getMemDC(), _UI_Garbage.rc.left, _UI_Garbage.rc.top);

	// 이미지 상태 출력
	for (int i = 0; i < 3; ++i)
	{
		//Rectangle(getMemDC(), _UI_State[i].rc);
		_UI_State[i].image->frameRender(getMemDC(), _UI_State[i].rc.left, _UI_State[i].rc.top,
			_UI_State[i].image->getFrameX(), 0);
	}

	// 인벤토리 렉트 출력
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//Rectangle(getMemDC(), _UI_Inventory[i][j].rc);
			IMAGEMANAGER->findImage("Select_Image")->render(getMemDC(), _UI_Inventory[i][j].rc.left, _UI_Inventory[i][j].rc.top);
		}
	}

}

void stageScene::posSetting()
{
	// 상태 UI 초기화
	_UI_State[PT_ERIC].image = new image;
	_UI_State[PT_ERIC].image = IMAGEMANAGER->findImage("R_State");

	_UI_State[PT_BALEOG].image = new image;
	_UI_State[PT_BALEOG].image = IMAGEMANAGER->findImage("A_State");

	_UI_State[PT_OLAF].image = new image;
	_UI_State[PT_OLAF].image = IMAGEMANAGER->findImage("S_State");


	_UI_State[PT_ERIC].pos.x = 185;
	_UI_State[PT_ERIC].pos.y = WINSIZEY - 95;

	_UI_State[PT_BALEOG].pos.x = 400;
	_UI_State[PT_BALEOG].pos.y = WINSIZEY - 95;

	_UI_State[PT_OLAF].pos.x = 615;
	_UI_State[PT_OLAF].pos.y = WINSIZEY - 95;

	_UI_State[PT_ERIC].rc = RectMakeCenter(_UI_State[PT_ERIC].pos.x, _UI_State[PT_ERIC].pos.y,
		_UI_State[PT_ERIC].image->getFrameWidth(), _UI_State[PT_ERIC].image->getFrameHeight());
	_UI_State[PT_ERIC].rc.left += 2;	// 삐져나온 위치 조정
	_UI_State[PT_ERIC].rc.right += 2;
	_UI_State[PT_ERIC].rc.top -= 2;
	_UI_State[PT_ERIC].rc.bottom -= 2;

	_UI_State[PT_BALEOG].rc = RectMakeCenter(_UI_State[PT_BALEOG].pos.x, _UI_State[PT_BALEOG].pos.y,
		_UI_State[PT_BALEOG].image->getFrameWidth(), _UI_State[PT_BALEOG].image->getFrameHeight());
	_UI_State[PT_BALEOG].rc.top -= 2;
	_UI_State[PT_BALEOG].rc.bottom -= 2;

	_UI_State[PT_OLAF].rc = RectMakeCenter(_UI_State[PT_OLAF].pos.x, _UI_State[PT_OLAF].pos.y,
		_UI_State[PT_OLAF].image->getFrameWidth(), _UI_State[PT_OLAF].image->getFrameHeight());
	_UI_State[PT_OLAF].rc.top -= 2;
	_UI_State[PT_OLAF].rc.bottom -= 2;

	// 시작 시엔 빨간놈이 선택되어 있다
	_UI_State[PT_ERIC].image->setFrameX(1);


	// 인벤토리 UI 초기화 (캐릭터마다 4개씩 있다.)
	for (int i = 0; i < 3; ++i)			// 캐릭터가 3개
	{
		for (int j = 0; j < 4; ++j)		// 인벤토리 4개
		{
			_UI_Inventory[i][j].image = new image;
			if (j < 2)
				_UI_Inventory[i][j].rc = RectMake(238 + (j * 48) + (i * 213), WINSIZEY - 138, 49, 48);		// 인벤토리 렉트
			else if (j < 4)
				_UI_Inventory[i][j].rc = RectMake(238 + ((j - 2) * 48) + (i * 213), WINSIZEY - 90, 49, 48);		// 인벤토리 렉트
			_UI_Inventory[i][j].pos.x = (_UI_Inventory[i][j].rc.left + _UI_Inventory[i][j].rc.right) / 2;		// 인벤토리 중심좌표
			_UI_Inventory[i][j].pos.y = (_UI_Inventory[i][j].rc.bottom + _UI_Inventory[i][j].rc.top) / 2;		// 인벤토리 중심좌표
		}
	}


	// 쓰레기통 UI 초기화
	_UI_Garbage.image = IMAGEMANAGER->findImage("GarbageBox");
	_UI_Garbage.rc = RectMake(764, _UI_State[PT_ERIC].rc.top, _UI_Garbage.image->getWidth(), _UI_Garbage.image->getHeight());
	_UI_Garbage.pos.x = (_UI_Garbage.rc.left + _UI_Garbage.rc.right) / 2;
	_UI_Garbage.pos.y = (_UI_Garbage.rc.top + _UI_Garbage.rc.bottom) / 2;

	// 캐릭터 전환 변수 (이 숫자가 바뀌면 그 캐릭터를 바라본다?)
	_charNum = PT_ERIC;


	// GiveUP 메뉴에 관한 내용
	// 캐릭터가 모두 죽었거나, Esc를 눌렀을때 들어가는 옵션이다.
	// 위치 초기화
	_UI_GiveUp[GU_CENTER];
	_UI_GiveUp[GU_YES];
	_UI_GiveUp[GU_NO];

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
	IMAGEMANAGER->addImage("Select_Image", "./image/UI/UI_Inventory/Select_Point.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Image", "./image/UI/UI_Inventory/UI_Image.bmp", 960, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Give_Center", "./image/UI/GiveUp/GiveUp.bmp", 156, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Give_Yes", "./image/UI/GiveUp/GiveUp.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Give_No", "./image/UI/GiveUp/GiveUp.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));
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
	_UI_State[PT_ERIC].dead = _pm->getPlayerEric().isDead;
	_UI_State[PT_BALEOG].dead = _pm->getPlayerBaleog().isDead;
	_UI_State[PT_OLAF].dead = _pm->getPlayerOlaf().isDead;

	// 만약 dead값이 true면 캐릭터가 죽었다는 뜻
	if (_UI_State[PT_ERIC].dead)
	{
		_UI_State[PT_ERIC].image->setFrameX(2);		// 이미지는 죽은 이미지로 교체한다.
	}

	if (_UI_State[PT_BALEOG].dead)
	{
		_UI_State[PT_BALEOG].image->setFrameX(2);	// 이미지는 죽은 이미지로 교체한다.
	}

	if (_UI_State[PT_OLAF].dead)
	{
		_UI_State[PT_OLAF].image->setFrameX(2);		// 이미지는 죽은 이미지로 교체한다.
	}

	// 만약 캐릭터가 죽었을 경우에 다음 캐릭터로 바꾸는 기능
	if (_UI_State[_charNum].dead)
	{
		while (true)
		{
			// 캐릭터가 모두 죽은 상황은 게임 오버 화면으로 넘어간다.
			if (_UI_State[PT_ERIC].dead && _UI_State[PT_BALEOG].dead && _UI_State[PT_OLAF].dead)
			{
				// 인터벌을 주고 넘어갈지 그냥 넘어갈지 정하고
				// 게임 오버 씬으로 넘어간다.
				// 임시로 인트로 씬으로 넘겼음
				_wm->init();		// 새로 시작하니까 모든 정보를 초기화 해준다.
				_pm->init();
				_em->init();

				// 인터벌을 주고 GiveUp에서 Yes에서 엔터를 누르면 게임오버씬으로 넘어간다.
				// 만약 No를 눌렀다면 타이틀 화면으로 넘어간다.
				SCENEMANAGER->set_SceneState(SS_GAMEOVER);
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

void stageScene::collisionMIX()
{
	
}
