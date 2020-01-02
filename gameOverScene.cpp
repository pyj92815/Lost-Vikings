#include "stdafx.h"
#include "gameOverScene.h"

gameOverScene::gameOverScene()
{

}

gameOverScene::~gameOverScene()
{
}

HRESULT gameOverScene::init()
{
	setting_Image();		// �ʿ��� �̹����� �����Ѵ�.
	setting_Pos();

	return S_OK;
}

void gameOverScene::release()
{
}

void gameOverScene::update()
{
	KEYANIMANAGER->update();
	restart_Select();		// ����� ���� ������
	letsGo_Ship();			// �踦 �����̴� �Լ�
}

void gameOverScene::render()
{
	_bg.image->aniRender(getMemDC(), _bg.rc.left, _bg.rc.top, _bg.ani);			// ��׶���
	_ship.image->aniRender(getMemDC(), _ship.rc.left, _ship.rc.top, _ship.ani);	// ��

	if (_ReStartGame.Re_Eric)	// ������ ����ִٸ� false�� ���� ���´�.
	{
		_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Eric].left, _goPlayerRC[GOP_Eric].top, GOP_Eric, 0);
	}

	if (!_ReStartGame.Re_Eric && _PlayerRE[GOP_Eric])		// ������ �׾��ִٸ� ture�� ���� ���´�. ���͸� ������ �������� ����ϸ� �ȵȴ�.
	{
		_goPCnt++;

		// ���� ���͸� �����ٸ� ������ ġ�� �� �ڿ� �� �ڸ��� ������ ��Ƴ���.
		_lightNing[GOP_Eric].image->aniRender(getMemDC(), _goPlayerRC[GOP_Eric].left + 30, -70, _lightNing[GOP_Eric].ani);

		if (_goPCnt == 50)
		{
			// ���͹��� �ְ� �� �Ŀ� ������ ���ڸ��� ��Ÿ����.
			_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Eric].left, _goPlayerRC[GOP_Eric].top, GOP_Eric, 0);
			_ReStartGame.Re_Eric = true;	// ������ ��Ƴ��ٴ� ǥ��
			_PlayerRE[GOP_Eric] = false;
			_goPCnt = 0;
		}
	}

	if (_ReStartGame.Re_Baleog)	// ���αװ� ����ִٸ� false�� ���� ���´�.
	{
		_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Baleog].left, _goPlayerRC[GOP_Baleog].top, GOP_Baleog, 0);
	}
	
	if (!_ReStartGame.Re_Baleog && _PlayerRE[GOP_Baleog])	// ���αװ� �׾��ִٸ� true�� ���� ���´�. ���Ͱ� ������ �������� ����ϸ� �ȵȴ�.
	{
		_goPCnt++;

		_lightNing[GOP_Baleog].image->aniRender(getMemDC(), _goPlayerRC[GOP_Baleog].left + 38, -20, _lightNing[GOP_Baleog].ani);

		if (_goPCnt == 50)
		{
			_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Baleog].left, _goPlayerRC[GOP_Baleog].top, GOP_Baleog, 0);
			_ReStartGame.Re_Baleog = true;	// ���αװ� ��Ƴ��ٴ� ǥ��
			_PlayerRE[GOP_Baleog] = false;
			_goPCnt = 0;
		}
	}
	
	if (_ReStartGame.Re_Olaf)	// �ö����� ����ִٸ� false�� ���� ���´�.
	{
		_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Olaf].left, _goPlayerRC[GOP_Olaf].top, GOP_Olaf, 0);
	}

	if (!_ReStartGame.Re_Olaf && _PlayerRE[GOP_Olaf])	// ���� �׾��ִٸ� ������� �ʴ´�.
	{
		_goPCnt++;

		_lightNing[GOP_Olaf].image->aniRender(getMemDC(), _goPlayerRC[GOP_Olaf].left + 38, -15, _lightNing[GOP_Olaf].ani);

		if (_goPCnt == 50)
		{
			_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Olaf].left, _goPlayerRC[GOP_Olaf].top, GOP_Olaf, 0);
			_ReStartGame.Re_Olaf = true;	// �ö����� ��Ƴ��ٴ� ǥ��
			_PlayerRE[GOP_Olaf] = false;
			_goPCnt = 0;
		}
	}

	//_goEric.image->aniRender(getMemDC(), _goEric.rc.left, _goEric.rc.top, _goEric.ani);
	//_goBaleog.image->aniRender(getMemDC(), _goBaleog.rc.left, _goBaleog.rc.top, _goBaleog.ani);
	//_goOlaf.image->aniRender(getMemDC(), _goOlaf.rc.left, _goOlaf.rc.top, _goOlaf.ani);
}

void gameOverScene::setting_Image()
{
	// ���ӿ������� �ʿ��� �̹����� �����Ѵ�.
	IMAGEMANAGER->addFrameImage("GO_BG", "./image/UI/GameOver/GameOver_BackGround.bmp", 6720, 758, 7, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("GO_Player", "./image/UI/GameOver/GameOver_Player.bmp", 600, 300, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GO_Ship", "./image/UI/GameOver/GameOver_Ship_Image.bmp", 600, 178, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GO_LightNing", "./image/UI/GameOver/GameOver_LightNing.bmp", 1200, 550, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Try_Center", "./image/UI/Try/Try_Center.bmp", 188, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Try_Yes", "./image/UI/Try/Try_Yes.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Try_No", "./image/UI/Try/Try_No.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));

	// �̹��� ������ �־��ش�.
	_bg.image = new image;
	_bg.image = IMAGEMANAGER->findImage("GO_BG");

	_ship.image = new image;
	_ship.image = IMAGEMANAGER->findImage("GO_Ship");

	for (int i = 0; i < 3; ++i)
	{
		_lightNing[i].image = new image;
		_lightNing[i].image = IMAGEMANAGER->findImage("GO_LightNing");
	}

	_goPlayer.image = new image;
	_goPlayer.image = IMAGEMANAGER->findImage("GO_Player");


	//_goEric.image = new image;
	//_goEric.image = IMAGEMANAGER->findImage("GO_Eric");
	//
	//_goBaleog.image = new image;
	//_goBaleog.image = IMAGEMANAGER->findImage("GO_Baleog");
	//
	//_goOlaf.image = new image;
	//_goOlaf.image = IMAGEMANAGER->findImage("GO_Olaf");

	int GO_BackGround[] = { 0,1,2,3,4,5,6 };
	// �ִ� Ű��, �̹��� Ű��, �迭, �迭����, �����Ӽӵ�, ��������
	KEYANIMANAGER->addArrayFrameAnimation("Ani_background", "GO_BG", GO_BackGround, 7, 5, true);
	
	int GO_Ship[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("Ani_ship", "GO_Ship", GO_Ship, 5, 6, true);

	int GO_LightNing[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("Ani_LightNing", "GO_LightNing", GO_LightNing, 9, 7, false);

	//int GO_P_Eric[] = { 0,1,2,3,4,5,6,7,8 };
	//KEYANIMANAGER->addArrayFrameAnimation("Ani_eric", "GO_Eric", GO_P_Eric, 9, 6, true);
	//
	//int GO_P_Baleog[] = { 0,1,2,3,4,5,6,7 };
	//KEYANIMANAGER->addArrayFrameAnimation("Ani_baleog", "GO_Baleog", GO_P_Baleog, 8, 6, true);
	//
	//int GO_P_Olaf[] = { 0,1,2,3,4,5,6,7,8 };
	//KEYANIMANAGER->addArrayFrameAnimation("Ani_olaf", "GO_Olaf", GO_P_Olaf, 9, 6, true);

	// �ִϸ��̼� ���� �־��ش�.
	_bg.ani = KEYANIMANAGER->findAnimation("Ani_background");
	
	_ship.ani = KEYANIMANAGER->findAnimation("Ani_ship");

	for (int i = 0; i < 3; ++i)
	{
		_lightNing[i].ani = KEYANIMANAGER->findAnimation("Ani_LightNing");
	}

	//_goEric.ani = KEYANIMANAGER->findAnimation("Ani_eric");
	//
	//_goBaleog.ani = KEYANIMANAGER->findAnimation("Ani_baleog");
	//
	//_goOlaf.ani = KEYANIMANAGER->findAnimation("Ani_olaf");

	_bg.ani->start();			// �� �׶��� �ִϸ��̼��� �����̵��� �Ѵ�.
	_ship.ani->start();			// ���� �ִϸ��̼��� �����̵��� �Ѵ�.
	//_goEric.ani->start();
	//_goBaleog.ani->start();
	//_goOlaf.ani->start();
}

void gameOverScene::setting_Pos()
{
	_bg.rc = RectMake(0, 0, WINSIZEX, WINSIZEY);							// ��׶��� ��ġ �ʱ�ȭ
	_ship.rc = RectMake(WINSIZEX / 2 - 30, WINSIZEY / 2 - 80, 430, 128);	// ���� ��ġ �ʱ�ȭ
	_goPlayerRC[GOP_Eric] = RectMake(45, WINSIZEY / 2 - 200, 100, 337);		// �÷��̾� ��ġ �ʱ�ȭ
	_goPlayerRC[GOP_Baleog] = RectMake(150, WINSIZEY / 2 - 150, 100, 337);
	_goPlayerRC[GOP_Olaf] = RectMake(300, WINSIZEY / 2 - 140, 100, 337);
	//_goEric.rc = RectMake(45, WINSIZEY/2 - 200, 100,337);
	//_goBaleog.rc = RectMake(150, WINSIZEY/2 - 150, 100, 337);
	//_goOlaf.rc = RectMake(250, WINSIZEY / 2 - 100, 100, 337);
}

void gameOverScene::letsGo_Ship()
{
	_ship.timer++;

	_ship.rc.left += 1;			// ��� õõ�� ���������� �̵��Ѵ�.
	_ship.rc.right += 1;

	if (_ship.timer == 15)		// Ÿ�̸��� ���� 15��� �� ���ǹ��� ���´�.
	{
		_ship.rc.top -= 1;		// Y������ ���ݾ� �̵��Ѵ�.
		_ship.rc.top -= 1;
		_ship.timer = 0;
	}

	// �踦 ���� ��ġ�� �ʱ�ȭ
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		_ship.rc = RectMake(WINSIZEX / 2 - 30, WINSIZEY / 2 - 80, 430, 128);
	}
}

void gameOverScene::restart_Select()
{
	// �÷��̾ ��� ��Ƴ� �ڿ� �޽��� ����� �Ѵ�.
	// ���� �޽����� �����⵵ ���� ���͸� �����ٸ� �ٷ� ���������� �̵��Ѵ�.
	// �޽������� Yes�� ������ ���������� ����.
	// �޽������� No�� ������ Ÿ��Ʋ ����ȭ������ ����.
	_goPLife = SCENEMANAGER->get_PlayerLife();

	// ĳ���Ͱ� ����ִٸ� ���� ������ �غ� �Ѵ�.
	if (!_goPLife[GOP_Eric])	_ReStartGame.Re_Eric = true;	// Stage������ �� ���� �޾Ƽ� �÷��̾ �ǻ츮��
	if (!_goPLife[GOP_Baleog])	_ReStartGame.Re_Baleog = true;	// �÷��̾ ��Ƴ��� ����Ʈ�� ���� ��� ���� �ʴ´�.
	if (!_goPLife[GOP_Olaf])	_ReStartGame.Re_Olaf = true;	// �÷��̾ ��� ��Ƴ��� init�� �̿��Ͽ� �ʵ带 �ʱ�ȭ�Ѵ�.

	// ���� �׾������� ���͸� �����ٸ� �츮�� �۾��� �����Ѵ�.
	if (_goPLife[GOP_Eric] && !_ReStartGame.Re_Eric)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_PlayerRE[GOP_Eric] = true;
			_lightNing[GOP_Eric].ani->start();	// ����Ʈ���� �ִϸ��̼��� �����̵��� �Ѵ�.
		}
	}

	else if (_goPLife[GOP_Baleog] && !_ReStartGame.Re_Baleog)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_PlayerRE[GOP_Baleog] = true;
			_lightNing[GOP_Baleog].ani->start();	// ����Ʈ���� �ִϸ��̼��� �����̵��� �Ѵ�.
		}
	}

	else if (_goPLife[GOP_Olaf] && !_ReStartGame.Re_Olaf)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_PlayerRE[GOP_Olaf] = true;
			_lightNing[GOP_Olaf].ani->start();	// ����Ʈ���� �ִϸ��̼��� �����̵��� �Ѵ�.
		}
	}

	// ���������� �̵����� Ÿ��Ʋ�� �̵����� �����ϴ� ȭ�� �ʿ�
}
