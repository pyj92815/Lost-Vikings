#include "stdafx.h"
#include "PlayerOlaf.h"


PlayerOlaf::PlayerOlaf()
{

}
PlayerOlaf::~PlayerOlaf()
{
}


HRESULT PlayerOlaf::init(float x, float y)
{
	// 올라프 이미지 선언
	IMAGEMANAGER->addFrameImage("Olaf_Idle_ShieldForward", "image/Characters/Olaf_Idle_ShieldForward.bmp", 93, 192, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_Idle_ShieldUp", "image/Characters/Olaf_Idle_ShieldUp.bmp", 84, 192, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_Move_ShieldForward", "image/Characters/Olaf_Move_ShieldForward.bmp", 776, 200, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_Move_ShieldUp", "image/Characters/Olaf_Move_ShieldUp.bmp", 522, 200, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_Push", "image/Characters/Olaf_Push.bmp", 392, 196, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_Climing", "image/Characters/Olaf_Climing.bmp", 324, 186, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_Climing_Start", "image/Characters/Olaf_Climing_Start.bmp", 186, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_Fall", "image/Characters/Olaf_Fall.bmp", 192, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_SlowFall", "image/Characters/Olaf_SlowFall.bmp", 190, 196, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Olaf_SlowFall_Land", "image/Characters/Olaf_SlowFall_Land.bmp", 171, 196, 2, 2, true, RGB(255, 0, 255));

	// 올라프 이미지, 좌표, 렉트, HP, 프레임 카운트,	 상태, 프레임 스피드, 쉴드 상태 선언
	_olaf.image = IMAGEMANAGER->findImage("Olaf_Idle_ShieldForward");
	_olaf.x = x;
	_olaf.y = y;
	_olaf.rc = RectMake(_olaf.x, _olaf.y, _olaf.image->getFrameWidth(), _olaf.image->getFrameHeight());
	_olaf.hp = 3;
	_olaf.frameCount = _olaf.currentFrameX = _olaf.currentFrameY = _olaf.gravity = 0;
	_olaf.posState = POSSTATE_AIR;
	_olaf.frameSpeed = 10;
	_probeY = _olaf.y + _olaf.image->getHeight() / 2;
	_isShieldUp = false;
	return S_OK;
}

void PlayerOlaf::release()
{

}

void PlayerOlaf::update()
{
	if (_stopControl) KeyControl();
	SetOlafState();
	SetOlafPosState();
	PixelCollision();

	// 픽셀 충돌을 위한 선언
	_olaf.frameCount++;

	_olaf.rc = RectMake(_olaf.x, _olaf.y, _olaf.image->getFrameWidth(), _olaf.image->getFrameHeight());
	if (_olaf.frameCount > _olaf.frameSpeed)
	{
		_olaf.currentFrameX++;
		_olaf.image->setFrameX(_olaf.currentFrameX);
		if (_olaf.currentFrameX > _olaf.image->getMaxFrameX())
		{
			_olaf.currentFrameX = 0;
		}
		_olaf.frameCount = 0;
	}
}

void PlayerOlaf::render()
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), _olaf.rc);
	}
	_olaf.image->frameRender(CAMERAMANAGER->getWorDC(), _olaf.x, _olaf.y, _olaf.currentFrameX, _olaf.currentFrameY);
}


void PlayerOlaf::KeyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_olaf.posState == POSSTATE_GROUND) _olaf.state = STATE_MOVE;
		_olaf.x -= PLAYER_SPEED;
		_olaf.currentFrameY = 1;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_olaf.posState == POSSTATE_GROUND) _olaf.state = STATE_IDLE;
		_olaf.currentFrameX = 0;
		_olaf.image->setFrameX(0);
		_olaf.frameCount = 0;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_olaf.posState == POSSTATE_GROUND) _olaf.state = STATE_MOVE;
		_olaf.x += PLAYER_SPEED;
		_olaf.currentFrameY = 0;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_olaf.posState == POSSTATE_GROUND) _olaf.state = STATE_IDLE;
		_olaf.currentFrameX = 0;
		_olaf.image->setFrameX(0);
		_olaf.frameCount = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('D') || KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isShieldUp = !_isShieldUp;
	}
}

void PlayerOlaf::SetOlafState()
{
	switch (_olaf.state)
	{
	case STATE_IDLE:
		if (!_isShieldUp)
			_olaf.image = IMAGEMANAGER->findImage("Olaf_Idle_ShieldForward");
		else
			_olaf.image = IMAGEMANAGER->findImage("Olaf_Idle_ShieldUp");
		break;

	case STATE_MOVE:
		if (!_isShieldUp)
			_olaf.image = IMAGEMANAGER->findImage("Olaf_Move_ShieldForward");
		else
			_olaf.image = IMAGEMANAGER->findImage("Olaf_Move_ShieldUp");
		break;
	case STATE_DIE:
		break;

	case STATE_POISON:
		break;

	case STATE_MIRRA:
		break;

	case STATE_PRESSDIE:
		break;

	case STATE_TRAPDIE:
		break;
	default:
		break;
	}
}

void PlayerOlaf::SetOlafPosState()
{
	switch (_olaf.posState)
	{
	case POSSTATE_GROUND:
		break;

	case POSSTATE_AIR:
		if (!_isShieldUp)
		{
			_olaf.image = IMAGEMANAGER->findImage("Olaf_Fall");
			_olaf.gravity += GRAVITY;
			_olaf.y += _olaf.gravity;
		}
		else
		{
			_olaf.image = IMAGEMANAGER->findImage("Olaf_SlowFall");
			_olaf.gravity = 2;
			_olaf.y += _olaf.gravity;
		}
		break;
	}
}

void PlayerOlaf::PixelCollision()
{
	_probeY = _olaf.y + _olaf.image->getHeight() / 2;

	// 플레이어 왼쪽 영역 픽셀 검색
	COLORREF getPixel_Left = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _olaf.rc.left, _olaf.rc.top);
	int r_left = GetRValue(getPixel_Left);
	int g_left = GetGValue(getPixel_Left);
	int b_left = GetBValue(getPixel_Left);

	// 플레이어 오른쪽 영역 픽셀 검색
	COLORREF getPixel_Right = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _olaf.rc.right, _olaf.rc.top);
	int r_right = GetRValue(getPixel_Right);
	int g_right = GetGValue(getPixel_Right);
	int b_right = GetBValue(getPixel_Right);

	// 플레이어 위쪽 영역 픽셀 검색
	COLORREF getPixel_Top = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_olaf.rc.right + _olaf.rc.left) / 2, _olaf.rc.top);
	int r_top = GetRValue(getPixel_Top);
	int g_top = GetGValue(getPixel_Top);
	int b_top = GetBValue(getPixel_Top);

	// 올라프 아래 영역 픽셀 검색
	for (int i = _probeY - 4; i < _probeY + 10; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_olaf.rc.right + _olaf.rc.left) / 2, i);
		int r_bottom = GetRValue(getPixel_Bottom);
		int g_bottom = GetGValue(getPixel_Bottom);
		int b_bottom = GetBValue(getPixel_Bottom);

		if (!(r_bottom == 255 && g_bottom == 0 && b_bottom == 255))
		{
			if (_olaf.gravity > 0)
			{
				_olaf.y -= (_olaf.gravity - 1);
				_olaf.gravity = 0;
			}

			_olaf.y = i - _olaf.image->getHeight() / 2;
			_olaf.posState = POSSTATE_GROUND;
			break;
		}
		else
		{
			_olaf.posState = POSSTATE_AIR;
		}
	}
}