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
	//����
	_ericJump = false;
	_eric.jumpPower = 15;
	_eric.movePower = 2;
	_eric.movePowerCount = 0;
	_eric.gravity = 0.3;
	//����
	_ericAttack = false;
	_ericUnable = false;
	_breathCount = 0;
	_breathFrameCount = 0;
	_test = RectMake(WINSIZEX / 2 + 200, WINSIZEY / 2, 200, 200);
	_gravity = 0; // �߷� 
	// �浹ó���� ���� �ȼ� ���κ�X/Y��
	_eric.probeX = _eric.x + _eric.image->getFrameWidth() / 2;
	_eric.probeY = _eric.y + _eric.image->getFrameHeight() / 2;
	return S_OK;
}

void playerEric::release()
{
}

void playerEric::update()
{
	if (!_ericUnable) key();		// ����Ű
	frameCount();					// �̹������������� 
	setEricImage();					// image ���� 
	ericJump();
	ericAttack();
	if (_ericUnable) ericAttackMove();
	_eric.rc = RectMake(_eric.x, _eric.y, _eric.image->getFrameWidth(), _eric.image->getFrameHeight());

	//�߷�
	if (_eric.posState == POSSTATE_AIR)
	{
		if(_gravity < 5)	 	_gravity += 0.7;
		_eric.y += _gravity;
	}

	//���� �� ��Ʈ���� �������ּ� 
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

	// 191229 PM 02:01 ������ �߰�
	// ������ ��ǥ�� ī�޶� �Ŵ����� �Ѱ��ش�.
	CAMERAMANAGER->set_Camera_XY(_eric.rc);

	// ������ �ƴϸ� �ȼ��浹, �����߿��� �ȼ��浹 
	if (!_ericJump)
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
	Rectangle(getMemDC(), _eric.rc);

	//Rectangle(getMemDC(), _test);

	// 191229 PM 03:17 ������ �׷����� ��ġ�� ����DC�� �Ȱ��.
	_eric.image->frameRender(CAMERAMANAGER->getWorDC(), _eric.x, _eric.y, _eric.currentFrameX, _eric.currentFrameY);
	// 191229 PM 04:27 UI���� ����� �ϱ� ���� �ּ�ó��
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
		_breathCount++; // ��ī��Ʈ 
		_eric.movePowerCount++;
		if (_eric.movePower <= 5)
		{
			if (_eric.movePowerCount > 4)
			{
				_eric.movePower += 0.2;
				_eric.movePowerCount = 0;
			}
		}

		if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP || _eric.state == STATE_PUSH)
		{
			_eric.x -= _eric.movePower;
			_eric.currentFrameY = 1;		 // 1�� ���� 
		}
		else
		{
			_eric.state = STATE_MOVE;
			_eric.frameSpeed = 10;
			_eric.x -= _eric.movePower;
			_eric.currentFrameY = 1;		 // 1�� ���� 
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_breathCount++; // ��ī��Ʈ 
		_eric.movePowerCount++;
		if (_eric.movePower <= 5)
		{
			if (_eric.movePowerCount > 4)
			{
				_eric.movePower += 0.2;
				_eric.movePowerCount = 0;
			}
		}

		if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP || _eric.state == STATE_PUSH)
		{
			_eric.x += _eric.movePower;
			_eric.currentFrameY = 0;		 // 0 �� ������ 
		}
		else
		{
			_eric.state = STATE_MOVE;
			_eric.frameSpeed = 10;
			_eric.x += _eric.movePower;
			_eric.currentFrameY = 0;		 // 0 �� ������ 
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		//_eric.movePowerCount = 0;
		//_eric.movePower = 2;
		if (_breathCount > 150)
		{
			_eric.state = STATE_BREATH;
			_eric.frameSpeed = 15;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(_eric.currentFrameX);
			_eric.movePower = 2;
			_breathCount = 0; // ��ī��Ʈ 
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
			_breathCount = 0; // ��ī��Ʈ 
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
			_eric.state = STATE_ERIC_JUMP;
			_eric.posState = POSSTATE_AIR; // �����̸� air
			_eric.jumpPower = 12;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(0);
			_eric.frameCount = 0;
			_eric.frameSpeed = 15;
			_ericJump = true;
			_jumpStart = _eric.y;
		}
	}


	// 191229 PM 03:18 �׽�Ʈ�� �̵�Ű �߰� (�����ؾ���)
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
	else
	{
		if (_eric.frameCount >= _eric.frameSpeed)
		{
			_eric.currentFrameX++;
			_eric.image->setFrameX(_eric.currentFrameX);
			if (_eric.currentFrameX > _eric.image->getMaxFrameX())
			{
				_eric.currentFrameX = 0;
				//������ ���� 
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
	// eric�� �� 
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
	//		// ���� �ε����� ������ ��ġ�� 
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
	// ������ ������ �ޤ��۷� �ٲܿ���
	// ������ 4�� �ø��� 4�� ����� 
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

void playerEric::isJumpPixelCollision()
{
	_eric.probeY = _eric.y + _eric.image->getFrameHeight();

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
