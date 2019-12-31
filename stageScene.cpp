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
	posSetting();	// UI의 좌표를 설정한다.

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	testStateImage();
}

void stageScene::render()
{
	// 테스트용 배경이다. 이후에는 지울것!
	//IMAGEMANAGER->findImage("Test_BG")->render(getMemDC(), 0, 0);


	//CAMERAMANAGER->get_WorImage()->render(getMemDC(), 0, 0);



	CAMERAMANAGER->get_WorImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(),
		CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

	//IMAGEMANAGER->findImage("OBJECT")->render(getMemDC(), 0, 0, CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(),
		//CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

	IMAGEMANAGER->findImage("UI_Image")->render(getMemDC(), 0, WINSIZEY - (WINSIZEY - 573));

	// 쓰레기통 출력
	_UI_Garbage.image->render(getMemDC(), _UI_Garbage.rc.left, _UI_Garbage.rc.top);

	// 테스트용 렉트 (캐릭터 상태 위치)
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
	

	// 쓰레기통 UI 초기화
	_UI_Garbage.image = IMAGEMANAGER->findImage("GarbageBox");
	_UI_Garbage.rc = RectMake(764, _UI_State[PT_ERIC].rc.top, _UI_Garbage.image->getWidth(), _UI_Garbage.image->getHeight());
	_UI_Garbage.pos.x = (_UI_Garbage.rc.left + _UI_Garbage.rc.right) / 2;
	_UI_Garbage.pos.y = (_UI_Garbage.rc.top + _UI_Garbage.rc.bottom) / 2;

	// 캐릭터 전환 변수 (이 숫자가 바뀌면 그 캐릭터를 바라본다?)
	_charNum = PT_ERIC;

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

	//// 테스트용 컨트롤을 누른다면
	//if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	//{
	//	_UI_State[_charNum].image->setFrameX(0);
	//	_charNum++;
	//	if (_charNum > PT_OLAF) _charNum = PT_ERIC;
	//	_UI_State[_charNum].image->setFrameX(1);
	//}

}
