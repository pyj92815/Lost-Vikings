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
	letsGo_Ship();
}

void gameOverScene::render()
{
	_bg.image->aniRender(getMemDC(), _bg.rc.left, _bg.rc.top, _bg.ani);
	_ship.image->aniRender(getMemDC(), _ship.rc.left, _ship.rc.top, _ship.ani);

	_goEric.image->aniRender(getMemDC(), _goEric.rc.left, _goEric.rc.top, _goEric.ani);
	_goBaleog.image->aniRender(getMemDC(), _goBaleog.rc.left, _goBaleog.rc.top, _goBaleog.ani);
	_goOlaf.image->aniRender(getMemDC(), _goOlaf.rc.left, _goOlaf.rc.top, _goOlaf.ani);
}

void gameOverScene::setting_Image()
{
	// 게임오버씬에 필요한 이미지를 저장한다.
	IMAGEMANAGER->addFrameImage("GO_BG", "./image/UI/GameOver/GameOver_BackGround.bmp", 6720, 758, 7, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("GO_Eric", "./image/UI/GameOver/GameOver_Player_Eric.bmp", 1251, 337, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GO_Olaf", "./image/UI/GameOver/GameOver_Player_Olaf.bmp", 1251, 337, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GO_Baleog", "./image/UI/GameOver/GameOver_Player_Baleog.bmp", 1024, 337, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GO_Ship", "./image/UI/GameOver/GameOver_Ship_Image.bmp", 600, 178, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Try_Center", "./image/UI/Try/Try_Center.bmp", 188, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Try_Yes", "./image/UI/Try/Try_Yes.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Try_No", "./image/UI/Try/Try_No.bmp", 100, 15, 2, 1, true, RGB(255, 0, 255));

	// 이미지 사진을 넣어준다.
	_bg.image = new image;
	_bg.image = IMAGEMANAGER->findImage("GO_BG");

	_ship.image = new image;
	_ship.image = IMAGEMANAGER->findImage("GO_Ship");

	_goEric.image = new image;
	_goEric.image = IMAGEMANAGER->findImage("GO_Eric");

	_goBaleog.image = new image;
	_goBaleog.image = IMAGEMANAGER->findImage("GO_Baleog");

	_goOlaf.image = new image;
	_goOlaf.image = IMAGEMANAGER->findImage("GO_Olaf");

	int GO_BackGround[] = { 0,1,2,3,4,5,6 };
	// 애니 키값, 이미지 키값, 배열, 배열길이, 프레임속도, 루프여부
	KEYANIMANAGER->addArrayFrameAnimation("Ani_background", "GO_BG", GO_BackGround, 7, 5, true);
	
	int GO_Ship[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("Ani_ship", "GO_Ship", GO_Ship, 5, 6, true);

	int GO_P_Eric[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("Ani_eric", "GO_Eric", GO_P_Eric, 9, 6, true);

	int GO_P_Baleog[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("Ani_baleog", "GO_Baleog", GO_P_Baleog, 8, 6, true);

	int GO_P_Olaf[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("Ani_olaf", "GO_Olaf", GO_P_Olaf, 9, 6, true);

	// 애니메이션 값을 넣어준다.
	_bg.ani = KEYANIMANAGER->findAnimation("Ani_background");
	
	_ship.ani = KEYANIMANAGER->findAnimation("Ani_ship");

	_goEric.ani = KEYANIMANAGER->findAnimation("Ani_eric");

	_goBaleog.ani = KEYANIMANAGER->findAnimation("Ani_baleog");

	_goOlaf.ani = KEYANIMANAGER->findAnimation("Ani_olaf");

	_bg.ani->start();
	_ship.ani->start();
	_goEric.ani->start();
	_goBaleog.ani->start();
	_goOlaf.ani->start();
}

void gameOverScene::setting_Pos()
{
	_bg.rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_ship.rc = RectMake(WINSIZEX / 2 - 30, WINSIZEY / 2 - 80, 430, 128);
	_goEric.rc = RectMake(45, WINSIZEY/2 - 200, 100,337);
	_goBaleog.rc = RectMake(150, WINSIZEY/2 - 150, 100, 337);
	_goOlaf.rc = RectMake(250, WINSIZEY / 2 - 100, 100, 337);
}

void gameOverScene::letsGo_Ship()
{
	_ship.timer++;
	_ship.rc.left += 1;
	_ship.rc.right += 1;
	if (_ship.timer == 15)
	{
		_ship.rc.top -= 1;
		_ship.rc.top -= 1;
		_ship.timer = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		_ship.rc = RectMake(WINSIZEX / 2 - 30, WINSIZEY / 2 - 80, 430, 128);
	}
}
