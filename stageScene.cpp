#include "stdafx.h"
#include "stageScene.h"


stageScene::stageScene()
{
	addStageImage();	// �̹��� �߰� �Լ�
}


stageScene::~stageScene()
{
}

HRESULT stageScene::init()
{
	posSetting();	// UI�� ��ǥ�� �����Ѵ�.

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
	// �׽�Ʈ�� ����̴�. ���Ŀ��� �����!
	//IMAGEMANAGER->findImage("Test_BG")->render(getMemDC(), 0, 0);

	IMAGEMANAGER->findImage("UI_Image")->render(getMemDC(), 0, WINSIZEY - (WINSIZEY - 573));

	// �������� ���
	_UI_Garbage.image->render(getMemDC(), _UI_Garbage.rc.left, _UI_Garbage.rc.top);

	// �׽�Ʈ�� ��Ʈ
	for (int i = 0; i < 3; ++i)
	{
		Rectangle(getMemDC(), _UI_State[i].rc);
		_UI_State[i].image->frameRender(getMemDC(), _UI_State[i].rc.left, _UI_State[i].rc.top,
			_UI_State[i].image->getFrameX(), 0);
	}

	CAMERAMANAGER->getWorImage()->render(getMemDC(), 0, 0,
		CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
}

void stageScene::posSetting()
{
	// ���� UI �ʱ�ȭ
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
	_UI_State[PT_Run].rc.left += 2;	// �������� ��ġ ����
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

	// ���� �ÿ� �������� ���õǾ� �ִ�
	_UI_State[PT_Run].image->setFrameX(1);


	// �κ��丮 UI �ʱ�ȭ (ĳ���͸��� 4���� �ִ�.)
	

	// �������� UI �ʱ�ȭ
	_UI_Garbage.image = IMAGEMANAGER->findImage("GarbageBox");
	_UI_Garbage.rc = RectMake(764, _UI_State[PT_Run].rc.top, _UI_Garbage.image->getWidth(), _UI_Garbage.image->getHeight());
	_UI_Garbage.pos.x = (_UI_Garbage.rc.left + _UI_Garbage.rc.right) / 2;
	_UI_Garbage.pos.y = (_UI_Garbage.rc.top + _UI_Garbage.rc.bottom) / 2;

	// ĳ���� ��ȯ ���� (�� ���ڰ� �ٲ�� �� ĳ���͸� �ٶ󺻴�?)
	_charNum = PT_Run;

}

void stageScene::addStageImage()
{
	// �������� UI���� ����� �̹����� �����Ѵ�.
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

	// �׽�Ʈ�� ��Ʈ���� �����ٸ�
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		_UI_State[_charNum].image->setFrameX(0);
		_charNum++;
		if (_charNum > PT_Def) _charNum = PT_Run;
		_UI_State[_charNum].image->setFrameX(1);
	}

}