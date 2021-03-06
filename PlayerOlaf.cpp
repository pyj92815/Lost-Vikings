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
	init_SettingOlafImg();

	// 올라프 이미지, 좌표, 렉트, HP, 프레임 카운트, 상태, 프레임 스피드, 쉴드 상태 선언
	_olaf.image = IMAGEMANAGER->findImage("Olaf_Idle_ShieldForward");
	_olaf.x = x;
	_olaf.y = y;
	_olaf.rc = RectMake(_olaf.x, _olaf.y, _olaf.image->getFrameWidth(), _olaf.image->getFrameHeight());
	_olaf.hp = 3;
	_olaf.frameCount = _olaf.currentFrameX = _olaf.currentFrameY = _olaf.gravity = 0;
	_olaf.posState = POSSTATE_AIR;
	_olaf.frameSpeed = 10;
	_isShieldUp = false;

	_testRect = RectMake(_olaf.x + 110, _olaf.y + 124, _olaf.image->getFrameWidth() - 4, 524);
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

	//CAMERAMANAGER->set_Camera_XY(_olaf.rc);
}

void PlayerOlaf::render()
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		char checkRGB[256];
		sprintf_s(checkRGB, sizeof(checkRGB), "R: %d G: %d B: %d", r_BC, g_BC, b_BC);
		Rectangle(CAMERAMANAGER->getWorDC(), _testRect);
		Rectangle(CAMERAMANAGER->getWorDC(), _olaf.rc);
		TextOut(CAMERAMANAGER->getWorDC(), _olaf.x, _olaf.y, checkRGB, strlen(checkRGB));
	}
	_olaf.image->frameRender(CAMERAMANAGER->getWorDC(), _olaf.x, _olaf.y, _olaf.currentFrameX, _olaf.currentFrameY);
}



void PlayerOlaf::init_SettingOlafImg()
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
		if (_olaf.posState == POSSTATE_GROUND)
		{
			_olaf.state = STATE_IDLE;
			_olaf.currentFrameX = 0;
			_olaf.image->setFrameX(0);
			_olaf.frameCount = 0;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_olaf.posState == POSSTATE_GROUND) _olaf.state = STATE_MOVE;
		_olaf.x += PLAYER_SPEED;
		_olaf.currentFrameY = 0;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_olaf.posState == POSSTATE_GROUND)
		{
			_olaf.state = STATE_IDLE;
			_olaf.currentFrameX = 0;
			_olaf.image->setFrameX(0);
			_olaf.frameCount = 0;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_olaf.state == STATE_STEPLADDEREND || _olaf.state == STATE_STEPLADDER)
		{
			_olaf.y -= PLAYER_SPEED;
			_olaf.x = (_testRect.right + _testRect.left) / 2 - _olaf.image->getCenterX();
		}
	}

	if (_olaf.state == STATE_STEPLADDEREND || _olaf.state == STATE_STEPLADDER)
	{
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if ((r_BC == 255 && g_BC == 0 && b_BC == 0))
			{
				_olaf.y += PLAYER_SPEED;
			}
			_olaf.x = (_testRect.right + _testRect.left) / 2 - _olaf.image->getCenterX();
		}
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
	// 플레이어 왼쪽 영역 픽셀 검색
	COLORREF getPixel_LT = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _olaf.rc.left, _olaf.rc.top);
	int r_LT = GetRValue(getPixel_LT);
	int g_LT = GetGValue(getPixel_LT);
	int b_LT = GetBValue(getPixel_LT);
	if (_olaf.posState == POSSTATE_GROUND && _olaf.state != STATE_STEPLADDEREND && _olaf.state != STATE_STEPLADDER) // 땅에 있을때
	{
		if (!(r_LT == 255 && g_LT == 0 && b_LT == 255))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_olaf.x += PLAYER_SPEED;
			}
		}
	}
	if (_olaf.posState != POSSTATE_GROUND || _olaf.state == STATE_STEPLADDEREND || _olaf.state == STATE_STEPLADDER) // 공중에 있을때
	{
		COLORREF getPixel_LB = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _olaf.rc.left, _olaf.rc.bottom);
		int r_LB = GetRValue(getPixel_LB);
		int g_LB = GetGValue(getPixel_LB);
		int b_LB = GetBValue(getPixel_LB);
		if (!(r_LB == 255 && g_LB == 0 && b_LB == 255) || !(r_LT == 255 && g_LT == 0 && b_LT == 255))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_olaf.x += PLAYER_SPEED;
			}
		}
	}

	// 플레이어 오른쪽 영역 픽셀 검색
	COLORREF getPixel_RT = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _olaf.rc.right, _olaf.rc.top);
	int r_RT = GetRValue(getPixel_RT);
	int g_RT = GetGValue(getPixel_RT);
	int b_RT = GetBValue(getPixel_RT);
	if (_olaf.posState == POSSTATE_GROUND && _olaf.state != STATE_STEPLADDEREND && _olaf.state != STATE_STEPLADDER) // 땅에 있을때
	{
		if (!(r_RT == 255 && g_RT == 0 && b_RT == 255))
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_olaf.x -= PLAYER_SPEED;
			}
		}
	}
	else if (_olaf.posState != POSSTATE_GROUND || _olaf.state == STATE_STEPLADDEREND || _olaf.state == STATE_STEPLADDER) // 공중에 있을때
	{
		COLORREF getPixel_RB = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _olaf.rc.right, _olaf.rc.bottom);
		int r_RB = GetRValue(getPixel_RB);
		int g_RB = GetGValue(getPixel_RB);
		int b_RB = GetBValue(getPixel_RB);
		if (!(r_RB == 255 && g_RB == 0 && b_RB == 255) || !(r_RT == 255 && g_RT == 0 && b_RT == 255))
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_olaf.x -= PLAYER_SPEED;
			}
		}
	}

	// 올라프 위 영역 픽셀 검색
	for (int i = _olaf.rc.top - 10; i < _olaf.rc.top + 4; i++)
	{
		getPixel_TC = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_olaf.rc.right + _olaf.rc.left) / 2, i);
		r_TC = GetRValue(getPixel_TC);
		g_TC = GetGValue(getPixel_TC);
		b_TC = GetBValue(getPixel_TC);

		if ((r_TC == 255 && g_TC == 0 && b_TC == 0))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				_olaf.state = STATE_STEPLADDER;
				_olaf.x = (_testRect.right + _testRect.left) / 2 - _olaf.image->getCenterX();
			}
			break;
		}
	}

	// 올라프 아래 영역 픽셀 검색
	for (int i = _olaf.rc.bottom - 4; i < _olaf.rc.bottom + 10; ++i)
	{
		getPixel_BC = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_olaf.rc.right + _olaf.rc.left) / 2, i);
		r_BC = GetRValue(getPixel_BC);
		g_BC = GetGValue(getPixel_BC);
		b_BC = GetBValue(getPixel_BC);

		if ((r_BC == 255 && g_BC == 255 && b_BC == 0)) // 일반 땅인 경우
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
		if ((r_BC == 255 && g_BC == 255 && b_BC == 0) && _olaf.state == STATE_STEPLADDER)
		{
			_olaf.y = i - _olaf.image->getHeight() / 2;
			_olaf.state = STATE_IDLE;
			_olaf.posState = POSSTATE_GROUND;
		}
		if ((r_BC == 255 && g_BC == 0 && b_BC == 255) && _olaf.state == STATE_STEPLADDER) // 사다리 탈출 시
		{
			_olaf.y = i - _olaf.image->getHeight() / 2;
			_olaf.state = STATE_IDLE;
			_olaf.posState = POSSTATE_GROUND;
		}
		else // 땅이 아니라면
		{
			_olaf.posState = POSSTATE_AIR;
		}

		if (r_BC == 255 && g_BC == 0 && b_BC == 0) // 사다리인 경우
		{
			if (_olaf.gravity > 0)
			{
				_olaf.y -= (_olaf.gravity - 1);
				_olaf.gravity = 0;
			}
			//_olaf.y = i - _olaf.image->getHeight() / 2;
			_olaf.posState = POSSTATE_GROUND;

			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				_olaf.state = STATE_STEPLADDER;
				_olaf.x = (_testRect.right + _testRect.left) / 2 - _olaf.image->getCenterX();
				_olaf.y += _olaf.image->getFrameHeight() * 0.2f;
			}
			break;
		}
	}
}
// 문제점 : 어떻게하면 검사해야하는 부분을 줄일 수 있을까? 지금 조건이 너무 많아서 이대로 가단 유지보수가 엄청 어려워 질수 있음.