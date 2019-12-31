#include "stdafx.h"
#include "playerEric.h"


playerEric::playerEric()
{
}


playerEric::~playerEric()
{
}

HRESULT playerEric::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("eric_die", "./image/Characters/eric_die.bmp", 792, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_idle", "./image/Characters/eric_idle.bmp", 156, 186, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_move", "./image/Characters/eric_move.bmp", 744, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_pressdie", "./image/Characters/eric_pressdie.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_poison", "./image/Characters/eric_poison.bmp", 630, 192, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_trapdie", "./image/Characters/eric_trapdie.bmp", 174, 186, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_stepladder", "./image/Characters/eric_stepladder.bmp", 336, 105, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_stepladderend", "./image/Characters/eric_stepladderend.bmp", 186, 78, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_jump", "./image/Characters/eric_jump.bmp", 372, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_push", "./image/Characters/eric_push.bmp", 372, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_headbutt", "./image/Characters/eric_headbutt.bmp", 888, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_headbuttend", "./image/Characters/eric_headbuttend.bmp", 990, 186, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_hitState", "./image/Characters/eric_hitState.bmp", 93, 192, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_breath", "./image/Characters/eric_breath.bmp", 270, 192, 3, 2, true, RGB(255, 0, 255));
	_eric.currentFrameX = _eric.currentFrameY = _eric.frameCount = 0;
	_eric.state = STATE_IDLE; //STATE_IDLE;
	_eric.posState = POSSTATE_GROUND;
	_eric.image = IMAGEMANAGER->findImage("eric_idle");
	_eric.hp = 3;
	_eric.x = x;
	_eric.y = y;
	_eric.frameSpeed = 15;
	_eric.rc = RectMake(_eric.x, _eric.y, _eric.image->getFrameWidth(), _eric.image->getFrameHeight());
	//점프
	_ericJump = false;
	_eric.jumpPower = 15;
	_eric.movePower = 3;
	_eric.movePowerCount = 0;
	_eric.gravity = 0.3;
	//공격
	_ericAttack = false;
	_ericUnable = false;
	_breathCount = 0;
	_breathFrameCount = 0;
	_test = RectMake(WINSIZEX / 2 + 200, WINSIZEY / 2, 200, 200);
	_gravity = 0; // 중력 
	// 슬라이딩
	_isSlide = false;
	_slidePower = 7;
	// 충돌처리를 위한 픽셀 프로브X/Y값
	_eric.probeX = _eric.x + _eric.image->getFrameWidth() / 2;
	_eric.probeY = _eric.y + _eric.image->getFrameHeight() / 2;
	return S_OK;
}

void playerEric::release()
{
}

void playerEric::update()
{
	if (!_ericUnable) key();		// 방향키
	frameCount();					// 이미지프레임증가 
	setEricImage();					// image 세팅 
	ericJump();
	ericAttack();
	if (_ericUnable) ericAttackMove();
	_eric.rc = RectMake(_eric.x, _eric.y, _eric.image->getFrameWidth(), _eric.image->getFrameHeight());

	//중력
	if (_eric.posState == POSSTATE_AIR)
	{
		PixelAirCollision();
		if (_gravity < 5)	 	_gravity += 0.7;
		_eric.y += _gravity;
		if (_eric.state != STATE_ERIC_JUMP)
		{
			_eric.state = STATE_ERIC_JUMP;
			_eric.currentFrameX = 2;
			_eric.image->setFrameX(_eric.currentFrameX);
		}
	}

	//맞을 때 히트값을 조정해주셈 
	if (_isHit)
	{
		_hitCount++;
		if (_eric.state != STATE_HIT)
		{
			_eric.state = STATE_HIT;
		}

		if (_hitCount > 10)
		{
			_isHit = false;
			_hitCount = 0;
			_eric.state = STATE_IDLE;
			_eric.frameCount = 0;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(_eric.currentFrameX);
		}
	}

	// 191229 PM 02:01 형길이 추가
	// 에릭의 좌표를 카메라 매니저에 넘겨준다.
	CAMERAMANAGER->set_Camera_XY(_eric.x, _eric.y);

	// 점프가 아니면 픽셀충돌, 점프중에도 픽셀충돌 

	if (_eric.posState == POSSTATE_GROUND)
	{
		PixelCollision();
	}
	else
	{
		isJumpPixelCollision();
	}
}

void playerEric::render()
{

	Rectangle(CAMERAMANAGER->getWorDC(), _eric.rc);

	//Rectangle(getMemDC(), _test);

	// 191229 PM 03:17 에릭이 그려지는 위치를 월드DC로 옴겼다.
	_eric.image->frameRender(CAMERAMANAGER->getWorDC(), _eric.x, _eric.y, _eric.currentFrameX, _eric.currentFrameY);
	// 191229 PM 04:27 UI에서 출력을 하기 위해 주석처리
	//CAMERAMANAGER->getWorImage()->render(getMemDC(), 0, 0,
	//	CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y()
	//	, CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());

	char str[100];
	sprintf_s(str, "%d", _breathCount);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
}

void playerEric::move()
{
}

void playerEric::key()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_eric.frameSpeed = 10;
		_eric.currentFrameY = 0;
		_breathCount = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_eric.frameSpeed = 10;
		_eric.currentFrameY = 1;
		_breathCount = 0;
	}



	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_eric.state = STATE_STEPLADDER;
		_eric.currentFrameY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		PixelLeftCollision();
		if (_eric.state == STATE_PUSH)
		{

		}
		else
		{
			_breathCount++; // 숨카운트 
			_eric.movePowerCount++;
			if (_eric.movePower <= 8)
			{
				if (_eric.movePowerCount > 4)
				{
					_eric.movePower += 0.5;
					_eric.movePowerCount = 0;
				}
			}

			if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP || _eric.state == STATE_PUSH)
			{
				_eric.x -= _eric.movePower;
			}
			else
			{
				_eric.state = STATE_MOVE;
				_eric.x -= _eric.movePower;
			}

			if (_isSlide)
			{
				_isSlideOn = true;
			}
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		PixelRightCollision();
		if (_eric.state == STATE_PUSH)
		{

		}
		else
		{
			_breathCount++; // 숨카운트 
			_eric.movePowerCount++;
			if (_eric.movePower <= 8)
			{
				if (_eric.movePowerCount > 4)
				{
					_eric.movePower += 0.5;
					_eric.movePowerCount = 0;
				}
			}

			if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP || _eric.state == STATE_PUSH)
			{
				_eric.x += _eric.movePower;
				// 0 이 오른쪽 
			}
			else
			{
				_eric.state = STATE_MOVE;
				_eric.x += _eric.movePower;	 // 0 이 오른쪽 
			}

			if (_isSlide)
			{
				_isSlideOn = true;
			}

		}
	}

	// 슬라이딩을 구성 

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_breathCount > 10 && _eric.state != STATE_PUSH)
		{
			_isSlide = true;
		}

		if (_breathCount > 150)
		{
			_eric.state = STATE_BREATH;
			_eric.frameSpeed = 15;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(_eric.currentFrameX);
			_eric.movePower = 2;
			_breathCount = 0; // 숨카운트 
		}
		else
		{
			if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP)
			{
				_eric.movePower = 3;
			}
			else
			{
				_eric.state = STATE_IDLE;
				_eric.movePower = 2;
				_eric.frameSpeed = 15;
				_eric.currentFrameX = 0;
			}
			_breathCount = 0; // 숨카운트 
		}
	}

	if (_isSlide)
	{
		_slideCount++;
		if (_slideCount > 5)
		{
			_slideCount = 0;
			_isSlide = false;
		}
	}

	if (_isSlideOn)
	{
		if (_eric.currentFrameY == 0)
		{
			_eric.x -= _slidePower;
		}
		else
		{
			_eric.x += _slidePower;
		}

		if (_slidePower >= 0)
		{
			_slidePower -= 0.1;
		}
		else
		{
			_slidePower = 7;
			_isSlideOn = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_eric.state = STATE_ERIC_HEADBUTT;
		_eric.frameSpeed = 6;
		_eric.currentFrameX = 0;
		_eric.image->setFrameX(0);
		_ericAttack = true;
	}
	if (!_ericJump)
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_ericJump = true;
			_eric.state = STATE_ERIC_JUMP;
			_eric.posState = POSSTATE_AIR; // 점프이면 air
			_eric.jumpPower = 14;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(0);
			_eric.frameCount = 0;
			_eric.frameSpeed = 15;
			_jumpStart = _eric.y;
		}
	}


	// 191229 PM 03:18 테스트용 이동키 추가 (삭제해야함)
	if (KEYMANAGER->isStayKeyDown('O'))
	{
		//_eric.y -= 5;
		_eric.y -= 20;
	}
	if (KEYMANAGER->isStayKeyDown('L'))
	{
		//_eric.y += 5;
		_eric.y+=20;
	}
}

void playerEric::frameCount()
{
	_eric.frameCount++;
	if (_eric.state == STATE_ERIC_HEADBUTT)
	{
		if (_eric.frameCount >= _eric.frameSpeed)
		{
			if (!_ericAttack)
			{
				_eric.currentFrameX--;
			}
			else
			{
				_eric.currentFrameX++;
			}

			_eric.image->setFrameX(_eric.currentFrameX);

			if (_eric.currentFrameX >= _eric.image->getMaxFrameX())
			{
				_ericAttack = false;
			}

			if (_eric.currentFrameX < 0)
			{
				_eric.state = STATE_IDLE;
				_eric.currentFrameX = 0;
			}
			_eric.frameCount = 0;
		}
	}
	else if (_eric.state == STATE_ERIC_HEADBUTTEND)
	{
		if (_eric.frameCount >= _eric.frameSpeed)
		{
			_eric.currentFrameX++;
			_eric.image->setFrameX(_eric.currentFrameX);


			if (_eric.currentFrameX > _eric.image->getMaxFrameX())
			{
				_ericUnable = false;
				_eric.currentFrameX = 0;
				_eric.state = STATE_IDLE;
			}
			_eric.frameCount = 0;
		}
	}
	else if (_eric.state == STATE_ERIC_JUMP)
	{
		if (_eric.frameCount >= _eric.frameSpeed)
		{
			if (_eric.currentFrameX == _eric.image->getMaxFrameX()) _eric.currentFrameX = _eric.currentFrameX - 2;
			if (_eric.currentFrameX < _eric.image->getMaxFrameX())
			{
				_eric.currentFrameX++;
				_eric.image->setFrameX(_eric.currentFrameX);
			}
			_eric.frameCount = 0;
		}
		if (_eric.posState == POSSTATE_GROUND)
		{
			_eric.state = STATE_IDLE;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(_eric.currentFrameX);
		}
	}
	else
	{
		if (_eric.frameCount >= _eric.frameSpeed)
		{
			_eric.currentFrameX++;
			_eric.image->setFrameX(_eric.currentFrameX);
			if (_eric.currentFrameX > _eric.image->getMaxFrameX())
			{
				_eric.currentFrameX = 0;
				//숨쉬기 위한 
				if (_eric.state == STATE_BREATH) _breathFrameCount++;
				if (_breathFrameCount > 3)
				{
					_eric.state = STATE_IDLE;
					_breathFrameCount = 0;
				}
			}
			_eric.frameCount = 0;
		}
	}
}

void playerEric::ericJump()
{
	if (_ericJump)
	{
		_eric.y -= _eric.jumpPower;
		_eric.jumpPower -= _eric.gravity;
		if (_jumpStart <= _eric.y && _eric.state == POSSTATE_AIR)
		{
			_eric.y = _jumpStart;
			_ericJump = false;
			_eric.state = STATE_IDLE;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(0);
		}
	}

}

void playerEric::ericAttack()
{
	// eric의 벽 
	//if (_eric.state != STATE_ERIC_HEADBUTT && _eric.state != STATE_ERIC_HEADBUTTEND)
	//{
	//	if (_test.left < _eric.x + _eric.image->getFrameWidth())
	//	{
	//		_eric.state = STATE_PUSH;
	//		if (_eric.image->getMaxFrameX() < _eric.currentFrameX)
	//		{
	//			_eric.currentFrameX = 0;
	//			_eric.image->setFrameX(_eric.currentFrameX);
	//		}
	//		_eric.x = _test.left - _eric.image->getFrameWidth();
	//	}
	//}

	//if (_eric.state == STATE_ERIC_HEADBUTT && _eric.currentFrameX > 3)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &_eric.rc, &_test))
	//	{
	//		// 벽을 부딪히면 에릭의 위치는 
	//		_eric.state = STATE_ERIC_HEADBUTTEND;
	//		_eric.currentFrameX = 0;
	//		_eric.image->setFrameX(0);
	//		_ericUnable = true;
	//		_eric.frameSpeed = 12;
	//	}
	//}
}

void playerEric::ericAttackMove()
{
	if (_eric.currentFrameY == 0)
	{
		_eric.x -= 0.3;
	}
	else
	{
		_eric.x += 0.3;
	}
	// 공식이 안좋음 앵ㅇ글로 바꿀예정
	// 프레임 4번 올리고 4번 낮춘다 
	if (_eric.currentFrameX >= 0 && _eric.currentFrameX < 4)
	{
		_eric.y -= 0.3;
	}
	else if (_eric.currentFrameX > 4 && _eric.currentFrameX < _eric.image->getMaxFrameX() - 1)
	{
		_eric.y += 0.3;
	}
}

void playerEric::setEricImage()
{
	switch (_eric.state)
	{
	case STATE_IDLE:
		_eric.image = IMAGEMANAGER->findImage("eric_idle");
		break;
	case STATE_MOVE:
		_eric.image = IMAGEMANAGER->findImage("eric_move");
		break;
	case STATE_ERIC_JUMP:
		_eric.image = IMAGEMANAGER->findImage("eric_jump");
		break;
	case STATE_ERIC_HEADBUTT:
		_eric.image = IMAGEMANAGER->findImage("eric_headbutt");
		break;
	case STATE_ERIC_HEADBUTTEND:
		_eric.image = IMAGEMANAGER->findImage("eric_headbuttend");
		break;
	case STATE_OLAF_GUARD:
		break;
	case STATE_OLAF_FLY:
		break;
	case STATE_BALEOG_ARROW:
		break;
	case STATE_BALEOG_SWORD:
		break;
	case STATE_BREATH:
		_eric.image = IMAGEMANAGER->findImage("eric_breath");
		break;
	case STATE_HIT:
		_eric.image = IMAGEMANAGER->findImage("eric_hitState");
		break;
	case STATE_PUSH:
		_eric.image = IMAGEMANAGER->findImage("eric_push");
		break;
	case STATE_DIE:
		_eric.image = IMAGEMANAGER->findImage("eric_die");
		break;
	case STATE_POISON:
		_eric.image = IMAGEMANAGER->findImage("eric_poison");
		break;
	case STATE_MIRRA:
		break;
	case STATE_PRESSDIE:
		_eric.image = IMAGEMANAGER->findImage("eric_pressdie");
		break;
	case STATE_TRAPDIE:
		_eric.image = IMAGEMANAGER->findImage("eric_trapdie");
		break;
	case STATE_STEPLADDER:
		_eric.image = IMAGEMANAGER->findImage("eric_stepladder");
		break;
	case STATE_STEPLADDEREND:
		_eric.image = IMAGEMANAGER->findImage("eric_stepladderend");
		break;
	}
}

void playerEric::PixelCollision()
{
	_eric.probeY = _eric.y + _eric.image->getFrameHeight();

	// 바닥 처리를 위한 픽셀 처리 
	for (int i = _eric.probeY - 4; i < _eric.probeY + 10; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_eric.rc.left + _eric.rc.right) / 2, i);

		int r = GetRValue(getPixel_Bottom);
		int g = GetGValue(getPixel_Bottom);
		int b = GetBValue(getPixel_Bottom);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_eric.y = i - _eric.image->getFrameHeight();
			_eric.posState = POSSTATE_GROUND;
			if (_gravity > 0)
			{
				_gravity = 0;
			}
			break;
		}
		else
		{
			_eric.posState = POSSTATE_AIR;
		}
	}

}

void playerEric::PixelRightCollision()
{
	if (_eric.state != STATE_PUSH) _eric.probeX = _eric.x + _eric.image->getFrameWidth(); // _eric.right  

	COLORREF getPixel_RIGHT = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _eric.probeX + 2, _eric.y);

	int r = GetRValue(getPixel_RIGHT);
	int g = GetGValue(getPixel_RIGHT);
	int b = GetBValue(getPixel_RIGHT);

	if (!(r == 255 && g == 0 && b == 255))
	{
		if (_eric.posState == POSSTATE_GROUND)
		{
			if (_eric.state != STATE_PUSH)
			{
				_eric.state = STATE_PUSH;
				_eric.currentFrameX = 0;
				_eric.image->setFrameX(0);
			}
		}
		_eric.x = _eric.probeX - _eric.image->getFrameWidth();
	}
}

void playerEric::PixelLeftCollision()
{
	if (_eric.state != STATE_PUSH) _eric.probeX = _eric.x - 3;

	COLORREF getPixel_LEFT = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _eric.probeX, _eric.y);

	int r = GetRValue(getPixel_LEFT);
	int g = GetGValue(getPixel_LEFT);
	int b = GetBValue(getPixel_LEFT);

	if (!(r == 255 && g == 0 && b == 255))
	{
		if (_eric.posState == POSSTATE_GROUND)
		{
			if (_eric.state != STATE_PUSH)
			{
				_eric.state = STATE_PUSH;
				_eric.currentFrameX = 0;
				_eric.image->setFrameX(0);
			}
		}
		_eric.x = _eric.probeX + 6;
	}
}


void playerEric::isJumpPixelCollision()
{
	_eric.probeY = _eric.y + _eric.image->getFrameHeight();

	for (int i = _eric.probeY; i < _eric.probeY + 10; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_eric.rc.left + _eric.rc.right) / 2, i);

		int r_Bottom = GetRValue(getPixel_Bottom);
		int g_Bottom = GetGValue(getPixel_Bottom);
		int b_Bottom = GetBValue(getPixel_Bottom);

		if (!(r_Bottom == 255 && g_Bottom == 0 && b_Bottom == 255) && _eric.currentFrameX > 0)
		{
			_eric.y = i - _eric.image->getFrameHeight();
			_eric.posState = POSSTATE_GROUND;
			if (_gravity > 0)
			{
				_gravity = 0;
			}
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(0);
			_ericJump = false;
			_eric.state = STATE_IDLE;
			break;
		}
		else
		{
			_eric.posState = POSSTATE_AIR;
		}
	}
}

void playerEric::PixelAirCollision()
{
	COLORREF getPixel_LB = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _eric.rc.left, _eric.rc.bottom);
	COLORREF getPixel_RB = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _eric.rc.right, _eric.rc.bottom);

	int r_LB = GetRValue(getPixel_LB);
	int g_LB = GetGValue(getPixel_LB);
	int b_LB = GetBValue(getPixel_LB);

	int r_RB = GetRValue(getPixel_RB);
	int g_RB = GetGValue(getPixel_RB);
	int b_RB = GetBValue(getPixel_RB);


	if (!(r_LB == 255 && g_LB == 0 && b_LB == 255))
	{
		if (_eric.currentFrameY == 1) // 왼쪽 
		{
			_eric.x = _eric.rc.left;
		}
	}

	if (!(r_RB == 255 && g_RB == 0 && b_RB == 255))
	{
		if (_eric.currentFrameY == 0) // 오른쪽 
		{
			_eric.x = _eric.rc.left;
		}
	}


}
