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
	_wm = new worldMap;
	_wm->init();

	_pm = new playerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	posSetting();	// UI�� ��ǥ�� �����Ѵ�. (ĳ���� ���� + �κ��丮)

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

	testStateImage();  // ĳ���� ��ȯ �׽�Ʈ
}

void stageScene::render()
{
	// �׽�Ʈ�� ����̴�. ���Ŀ��� �����!
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

	// �������� ���
	_UI_Garbage.image->render(getMemDC(), _UI_Garbage.rc.left, _UI_Garbage.rc.top);

	// �̹��� ���� ���
	for (int i = 0; i < 3; ++i)
	{
		//Rectangle(getMemDC(), _UI_State[i].rc);
		_UI_State[i].image->frameRender(getMemDC(), _UI_State[i].rc.left, _UI_State[i].rc.top,
			_UI_State[i].image->getFrameX(), 0);
	}

	// �κ��丮 ��Ʈ ���
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
	// ���� UI �ʱ�ȭ
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
	_UI_State[PT_ERIC].rc.left += 2;	// �������� ��ġ ����
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

	// ���� �ÿ� �������� ���õǾ� �ִ�
	_UI_State[PT_ERIC].image->setFrameX(1);


	// �κ��丮 UI �ʱ�ȭ (ĳ���͸��� 4���� �ִ�.)
	for (int i = 0; i < 3; ++i)			// ĳ���Ͱ� 3��
	{
		for (int j = 0; j < 4; ++j)		// �κ��丮 4��
		{
			_UI_Inventory[i][j].image = new image;
			if (j < 2)
				_UI_Inventory[i][j].rc = RectMake(238 + (j * 48) + (i * 213), WINSIZEY - 138, 49, 48);		// �κ��丮 ��Ʈ
			else if (j < 4)
				_UI_Inventory[i][j].rc = RectMake(238 + ((j - 2) * 48) + (i * 213), WINSIZEY - 90, 49, 48);		// �κ��丮 ��Ʈ
			_UI_Inventory[i][j].pos.x = (_UI_Inventory[i][j].rc.left + _UI_Inventory[i][j].rc.right) / 2;		// �κ��丮 �߽���ǥ
			_UI_Inventory[i][j].pos.y = (_UI_Inventory[i][j].rc.bottom + _UI_Inventory[i][j].rc.top) / 2;		// �κ��丮 �߽���ǥ
		}
	}


	// �������� UI �ʱ�ȭ
	_UI_Garbage.image = IMAGEMANAGER->findImage("GarbageBox");
	_UI_Garbage.rc = RectMake(764, _UI_State[PT_ERIC].rc.top, _UI_Garbage.image->getWidth(), _UI_Garbage.image->getHeight());
	_UI_Garbage.pos.x = (_UI_Garbage.rc.left + _UI_Garbage.rc.right) / 2;
	_UI_Garbage.pos.y = (_UI_Garbage.rc.top + _UI_Garbage.rc.bottom) / 2;

	// ĳ���� ��ȯ ���� (�� ���ڰ� �ٲ�� �� ĳ���͸� �ٶ󺻴�?)
	_charNum = PT_ERIC;


	// GiveUP �޴��� ���� ����
	// ĳ���Ͱ� ��� �׾��ų�, Esc�� �������� ���� �ɼ��̴�.
	// ��ġ �ʱ�ȭ
	_UI_GiveUp[GU_CENTER];
	_UI_GiveUp[GU_YES];
	_UI_GiveUp[GU_NO];

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
	IMAGEMANAGER->addImage("Select_Image", "./image/UI/UI_Inventory/Select_Point.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Image", "./image/UI/UI_Inventory/UI_Image.bmp", 960, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Give_Center", "./image/UI/GiveUp/GiveUp.bmp", 156, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Give_Yes", "./image/UI/GiveUp/GiveUp.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Give_No", "./image/UI/GiveUp/GiveUp.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));
}

void stageScene::testStateImage()
{

	// �׽�Ʈ�� ��Ʈ���� �����ٸ�
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		//_UI_State[_charNum].image->setFrameX(0);
		//_charNum++;
		//if (_charNum > PT_Def) _charNum = PT_Run;
		//_UI_State[_charNum].image->setFrameX(1);

		_UI_State[_charNum].image->setFrameX(0);	// ĳ���Ͱ� ��ü�Ǹ� ������ �ִ� ĳ���ʹ� 0�� �̹����� ����
		_charNum++;									// ���� ĳ���͸� ���� ���ڸ� ���������ش�.
		if (_charNum == 3)	_charNum = 0;			// ���� ĳ������ ������ �Ѿ��
		if (_UI_State[_charNum].dead)
		{
			_charNum++;								// ���� ���� ĳ���Ͱ� �׾��ִٸ�, ���� ĳ���͸� ��ȸ�Ѵ�.
			if (_charNum == 3)	_charNum = 0;			// ���� ĳ������ ������ �Ѿ��

			if (_UI_State[_charNum].dead)
				_charNum++;
			if (_charNum == 3)	_charNum = 0;			// ���� ĳ������ ������ �Ѿ��
		}
		_UI_State[_charNum].image->setFrameX(1);

		// ��Ȳ�� �°� ī�޶� ��ǥ�� �Ѱ�����Ѵ�.
		// ���� ĳ���Ͱ� �ƴ϶�� 0�� �̹����� ������ֵ��� �ٲ��ش�.
		// ĳ���Ͱ� ���õǾ� �ִ� ��Ȳ�̶�� 1�� �̹����� ����Ѵ�.

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
	// ĳ������ ���� ������ �޾Ƽ� �����Ѵ�.
	// ���� ĳ���Ͱ� �׾��ٸ� ���� �̹����� �׾��ְ� �Ѵ�.
	_UI_State[PT_ERIC].dead = _pm->getPlayerEric().isDead;
	_UI_State[PT_BALEOG].dead = _pm->getPlayerBaleog().isDead;
	_UI_State[PT_OLAF].dead = _pm->getPlayerOlaf().isDead;

	// ���� dead���� true�� ĳ���Ͱ� �׾��ٴ� ��
	if (_UI_State[PT_ERIC].dead)
	{
		_UI_State[PT_ERIC].image->setFrameX(2);		// �̹����� ���� �̹����� ��ü�Ѵ�.
	}

	if (_UI_State[PT_BALEOG].dead)
	{
		_UI_State[PT_BALEOG].image->setFrameX(2);	// �̹����� ���� �̹����� ��ü�Ѵ�.
	}

	if (_UI_State[PT_OLAF].dead)
	{
		_UI_State[PT_OLAF].image->setFrameX(2);		// �̹����� ���� �̹����� ��ü�Ѵ�.
	}

	// ���� ĳ���Ͱ� �׾��� ��쿡 ���� ĳ���ͷ� �ٲٴ� ���
	if (_UI_State[_charNum].dead)
	{
		while (true)
		{
			// ĳ���Ͱ� ��� ���� ��Ȳ�� ���� ���� ȭ������ �Ѿ��.
			if (_UI_State[PT_ERIC].dead && _UI_State[PT_BALEOG].dead && _UI_State[PT_OLAF].dead)
			{
				// ���͹��� �ְ� �Ѿ�� �׳� �Ѿ�� ���ϰ�
				// ���� ���� ������ �Ѿ��.
				// �ӽ÷� ��Ʈ�� ������ �Ѱ���
				_wm->init();		// ���� �����ϴϱ� ��� ������ �ʱ�ȭ ���ش�.
				_pm->init();
				_em->init();

				// ���͹��� �ְ� GiveUp���� Yes���� ���͸� ������ ���ӿ��������� �Ѿ��.
				// ���� No�� �����ٸ� Ÿ��Ʋ ȭ������ �Ѿ��.
				SCENEMANAGER->set_SceneState(SS_GAMEOVER);
				break;
			}

			_charNum++;

			if (!_UI_State[_charNum].dead)
			{
				_UI_State[_charNum].image->setFrameX(1);	// ĳ���Ͱ� ���������ϱ� ĳ���͸� ���ش�.
				break;										// ���� ���� ĳ���Ͱ� ���� �ʾҴٸ� ���Ϲ� ������
			}

			if (_charNum == 3)	_charNum = 0;				// ���� ĳ������ ������ �ʰ��ߴٸ� �ٽ� 0������
		}
	}
}

void stageScene::collisionMIX()
{
	
}
