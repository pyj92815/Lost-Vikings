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
	setting_Image();		// 필요한 이미지를 세팅한다.
	setting_Pos();

	return S_OK;
}

void gameOverScene::release()
{
}

void gameOverScene::update()
{
	KEYANIMANAGER->update();
	restart_Select();		// 재시작 할지 안할지
	letsGo_Ship();			// 배를 움직이는 함수
}

void gameOverScene::render()
{
	_bg.image->aniRender(getMemDC(), _bg.rc.left, _bg.rc.top, _bg.ani);			// 백그라운드
	_ship.image->aniRender(getMemDC(), _ship.rc.left, _ship.rc.top, _ship.ani);	// 배

	if (_ReStartGame.Re_Eric)	// 에릭이 살아있다면 false의 값을 갖는다.
	{
		_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Eric].left, _goPlayerRC[GOP_Eric].top, GOP_Eric, 0);
	}

	if (!_ReStartGame.Re_Eric && _PlayerRE[GOP_Eric])		// 에릭이 죽어있다면 ture의 값을 갖는다. 엔터를 누르기 전까지는 출력하면 안된다.
	{
		_goPCnt++;

		// 만약 엔터를 누른다면 번개가 치고 난 뒤에 그 자리에 에릭이 살아난다.
		_lightNing[GOP_Eric].image->aniRender(getMemDC(), _goPlayerRC[GOP_Eric].left + 30, -70, _lightNing[GOP_Eric].ani);

		if (_goPCnt == 50)
		{
			// 인터벌을 주고 그 후에 에릭이 그자리에 나타난다.
			_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Eric].left, _goPlayerRC[GOP_Eric].top, GOP_Eric, 0);
			_ReStartGame.Re_Eric = true;	// 에릭이 살아났다는 표시
			_PlayerRE[GOP_Eric] = false;
			_goPCnt = 0;
		}
	}

	if (_ReStartGame.Re_Baleog)	// 벨로그가 살아있다면 false의 값을 갖는다.
	{
		_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Baleog].left, _goPlayerRC[GOP_Baleog].top, GOP_Baleog, 0);
	}
	
	if (!_ReStartGame.Re_Baleog && _PlayerRE[GOP_Baleog])	// 벨로그가 죽어있다면 true의 값을 갖는다. 엔터가 누르기 전까지는 출력하면 안된다.
	{
		_goPCnt++;

		_lightNing[GOP_Baleog].image->aniRender(getMemDC(), _goPlayerRC[GOP_Baleog].left + 38, -20, _lightNing[GOP_Baleog].ani);

		if (_goPCnt == 50)
		{
			_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Baleog].left, _goPlayerRC[GOP_Baleog].top, GOP_Baleog, 0);
			_ReStartGame.Re_Baleog = true;	// 벨로그가 살아났다는 표시
			_PlayerRE[GOP_Baleog] = false;
			_goPCnt = 0;
		}
	}
	
	if (_ReStartGame.Re_Olaf)	// 올라프가 살아있다면 false의 값을 갖는다.
	{
		_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Olaf].left, _goPlayerRC[GOP_Olaf].top, GOP_Olaf, 0);
	}

	if (!_ReStartGame.Re_Olaf && _PlayerRE[GOP_Olaf])	// 만약 죽어있다면 출력하지 않는다.
	{
		_goPCnt++;

		_lightNing[GOP_Olaf].image->aniRender(getMemDC(), _goPlayerRC[GOP_Olaf].left + 38, -15, _lightNing[GOP_Olaf].ani);

		if (_goPCnt == 50)
		{
			_goPlayer.image->frameRender(getMemDC(), _goPlayerRC[GOP_Olaf].left, _goPlayerRC[GOP_Olaf].top, GOP_Olaf, 0);
			_ReStartGame.Re_Olaf = true;	// 올라프가 살아났다는 표시
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
	// 게임오버씬에 필요한 이미지를 저장한다.
	IMAGEMANAGER->addFrameImage("GO_BG", "./image/UI/GameOver/GameOver_BackGround.bmp", 6720, 758, 7, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("GO_Player", "./image/UI/GameOver/GameOver_Player.bmp", 600, 300, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GO_Ship", "./image/UI/GameOver/GameOver_Ship_Image.bmp", 600, 178, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GO_LightNing", "./image/UI/GameOver/GameOver_LightNing.bmp", 1200, 550, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Try_Center", "./image/UI/Try/Try_Center.bmp", 188, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Try_Yes", "./image/UI/Try/Try_Yes.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Try_No", "./image/UI/Try/Try_No.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));

	// 이미지 사진을 넣어준다.
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
	// 애니 키값, 이미지 키값, 배열, 배열길이, 프레임속도, 루프여부
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

	// 애니메이션 값을 넣어준다.
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

	_bg.ani->start();			// 백 그라운드 애니메이션을 움직이도록 한다.
	_ship.ani->start();			// 배의 애니메이션을 움직이도록 한다.
	//_goEric.ani->start();
	//_goBaleog.ani->start();
	//_goOlaf.ani->start();
}

void gameOverScene::setting_Pos()
{
	_bg.rc = RectMake(0, 0, WINSIZEX, WINSIZEY);							// 백그라운드 위치 초기화
	_ship.rc = RectMake(WINSIZEX / 2 - 30, WINSIZEY / 2 - 80, 430, 128);	// 배의 위치 초기화
	_goPlayerRC[GOP_Eric] = RectMake(45, WINSIZEY / 2 - 200, 100, 337);		// 플레이어 위치 초기화
	_goPlayerRC[GOP_Baleog] = RectMake(150, WINSIZEY / 2 - 150, 100, 337);
	_goPlayerRC[GOP_Olaf] = RectMake(300, WINSIZEY / 2 - 140, 100, 337);
	//_goEric.rc = RectMake(45, WINSIZEY/2 - 200, 100,337);
	//_goBaleog.rc = RectMake(150, WINSIZEY/2 - 150, 100, 337);
	//_goOlaf.rc = RectMake(250, WINSIZEY / 2 - 100, 100, 337);
}

void gameOverScene::letsGo_Ship()
{
	_ship.timer++;

	_ship.rc.left += 1;			// 배는 천천히 오른쪽으로 이동한다.
	_ship.rc.right += 1;

	if (_ship.timer == 15)		// 타이머의 값이 15라면 이 조건문에 들어온다.
	{
		_ship.rc.top -= 1;		// Y축으로 조금씩 이동한다.
		_ship.rc.top -= 1;
		_ship.timer = 0;
	}

	// 배를 시작 위치로 초기화
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		_ship.rc = RectMake(WINSIZEX / 2 - 30, WINSIZEY / 2 - 80, 430, 128);
	}
}

void gameOverScene::restart_Select()
{
	// 플레이어가 모두 살아난 뒤에 메시지 출력을 한다.
	// 만약 메시지가 나오기도 전에 엔터를 누른다면 바로 스테이지로 이동한다.
	// 메시지에서 Yes를 누르면 스테이지로 간다.
	// 메시지에서 No를 누르면 타이틀 선택화면으로 간다.
	_goPLife = SCENEMANAGER->get_PlayerLife();

	// 캐릭터가 살아있다면 새로 시작할 준비를 한다.
	if (!_goPLife[GOP_Eric])	_ReStartGame.Re_Eric = true;	// Stage씬에서 이 값을 받아서 플레이어를 되살리고
	if (!_goPLife[GOP_Baleog])	_ReStartGame.Re_Baleog = true;	// 플레이어가 살아나면 라이트닝 씬이 출력 되지 않는다.
	if (!_goPLife[GOP_Olaf])	_ReStartGame.Re_Olaf = true;	// 플레이어가 모두 살아나면 init을 이용하여 필드를 초기화한다.

	// 만약 죽어있을때 엔터를 눌렀다면 살리는 작업을 시작한다.
	if (_goPLife[GOP_Eric] && !_ReStartGame.Re_Eric)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_PlayerRE[GOP_Eric] = true;
			_lightNing[GOP_Eric].ani->start();	// 라이트닝의 애니메이션을 움직이도록 한다.
		}
	}

	else if (_goPLife[GOP_Baleog] && !_ReStartGame.Re_Baleog)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_PlayerRE[GOP_Baleog] = true;
			_lightNing[GOP_Baleog].ani->start();	// 라이트닝의 애니메이션을 움직이도록 한다.
		}
	}

	else if (_goPLife[GOP_Olaf] && !_ReStartGame.Re_Olaf)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_PlayerRE[GOP_Olaf] = true;
			_lightNing[GOP_Olaf].ani->start();	// 라이트닝의 애니메이션을 움직이도록 한다.
		}
	}

	// 스테이지로 이동할지 타이틀로 이동할지 선택하는 화면 필요
}
