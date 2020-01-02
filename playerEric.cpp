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
	IMAGEMANAGER->addFrameImage("eric_jump", "./image/Characters/eric_jump.bmp", 372, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_push", "./image/Characters/eric_push.bmp", 372, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_breath", "./image/Characters/eric_breath.bmp", 270, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_poison", "./image/Characters/eric_poison.bmp", 630, 192, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_trapdie", "./image/Characters/eric_trapdie.bmp", 174, 186, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_hitState", "./image/Characters/eric_hitState.bmp", 93, 192, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_pressdie", "./image/Characters/eric_pressdie.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_headbutt", "./image/Characters/eric_headbutt.bmp", 888, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_mirra.bmp", "./image/Characters/eric_mirraddie.bmp", 216, 180, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_stepladder", "./image/Characters/eric_stepladder.bmp", 336, 105, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_headbuttend", "./image/Characters/eric_headbuttend.bmp", 990, 186, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("eric_stepladderend", "./image/Characters/eric_stepladderend.bmp", 186, 78, 2, 1, true, RGB(255, 0, 255));

	_eric.currentFrameX = _eric.currentFrameY = _eric.frameCount = 0;		 // ������ �ʱⰪ 
	_eric.frameSpeed = 15;												     // ������ ���ǵ� �ʱⰪ
	_eric.state = STATE_IDLE;												 // ���°� �ʱⰪ
	_eric.posState = POSSTATE_GROUND;										 // ��ġ   �ʱⰪ
	_eric.image = IMAGEMANAGER->findImage("eric_idle");						 // �̹��� �ʱⰪ
	_eric.x = x;															 // x 
	_eric.y = y;															 // y
	_eric.rc = RectMake(_eric.x, _eric.y, _eric.image->getFrameWidth(), _eric.image->getFrameHeight());   // RECT
	
	_eric.hp = 3;		
	_eric.isDead = false;// ü�� 
	//========================== ���� ���� ==================================//
	_ericJump = false;					
	_eric.jumpPower = 15;
	_eric.gravity = 0.3;
	//========================== �̵� ���� ==================================//
	_eric.movePower = 2;
	_eric.movePowerCount = 0;
	//========================== ���� ���� ==================================//
	_ericAttack = false;
	_ericUnable = false;
	//========================== Ư�� ��Ȳ ���� =============================//
	_breathCount = 0;
	_breathFrameCount = 0;
	

	_gravity = 0;			// ERIC AIR ������ �� �߷� 
	_slidePower = 7;		// 
	_isSlide = false;		// �����̵� 
	//========================== �浹ó�� �ʱ�ȭ ============================//
	_eric.probeX = _eric.x + _eric.image->getFrameWidth() / 2;
	_eric.probeY = _eric.y + _eric.image->getFrameHeight() / 2;
	return S_OK;
}

void playerEric::release()
{
}

void playerEric::update()
{

	if (_stopControl)				// �ɸ��� ���� BOOL��
	{
		if (!_ericUnable) key();	// ���� �Ҵ� ���°� �ƴϸ� key�� 
	}	
	ericFrameCount();				// �̹��� ������ ���� 
	setEricImage();					// image ���� 
	if (!_ericUnable)
	{


	ericJump();						// ���� 
	ericHit();						// ���� �� �̹��� 
		//======================���� ����==================//
	ericAttack();							// ���� 
	if (_ericUnable) ericAttackMove();		// �����ϸ� ƨ�ܳ����� �Լ� 



	// ������ ��ǥ�� ī�޶� �Ŵ����� �Ѱ��ش�.
	// CAMERAMANAGER->set_Camera_XY(_eric.rc);
	// ������ ��ġ�� �׶����̸� 
	// ������ �ƴϸ� �ȼ��浹, �����߿��� �ȼ��浹 

	if (_eric.posState == POSSTATE_AIR)
	{
		isJumpPixelCollision();

		// �߷°� 
		if (_gravity < 5)	 _gravity += 0.7;
		_eric.y += _gravity;
		if (_eric.state != STATE_ERIC_JUMP) // ������ �� �����ϸ鼭 �������� ���� 
		{
			_eric.state = STATE_ERIC_JUMP;
			_eric.currentFrameX = 2;
			_eric.image->setFrameX(_eric.currentFrameX);
		}
	}
	else if(_eric.posState == POSSTATE_GROUND)// ������ ��ġ�� �������̸� 
	{
		PixelCollision();
	}
	}
	//  �÷��̾� ���
	ericDie();
	_eric.rc = RectMake(_eric.x, _eric.y, _eric.image->getFrameWidth(), _eric.image->getFrameHeight());   // RECT ����
}

void playerEric::render()
{

	// �ӽ� ������ �� 

	//Rectangle(getMemDC(), _test);

	// 191229 PM 03:17 ������ �׷����� ��ġ�� ����DC�� �Ȱ��.
	Rectangle(CAMERAMANAGER->getWorDC(), _eric.rc);
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
	//���࿡ �¿� Ű�� ������ 
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_eric.frameSpeed = 10;
		_breathCount = 0;
		if (_eric.state != STATE_PUSH) _eric.currentFrameY = 0;
		if (_isSlide && _eric.state != STATE_PUSH)  _isSlideOn = true;		// �����̵��� Ȱ��ȭ ��Ű�� ���� 
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_eric.frameSpeed = 10;
		_breathCount = 0;
		if(_eric.state != STATE_PUSH) _eric.currentFrameY = 1;
		if (_isSlide && _eric.state != STATE_PUSH)   _isSlideOn = true;		// �����̵��� Ȱ��ȭ ��Ű�� ���� 
	}


	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_eric.state = STATE_STEPLADDER;
		_eric.currentFrameY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
	}

	// ���� Ű�� ���������� ������ 
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		// ���� �ȼ� �浹 
		PixelLeftCollision();
		if (_eric.state != STATE_PUSH)
		{
			_breathCount++;						 // ���� �ٸ� �� �̹����� ��Ÿ�� 
			//==========�̵� ���õ� �ڵ� =========//
			_eric.movePowerCount++;				 
			if (_eric.movePower <= 8)
			{
				if (_eric.movePowerCount > 4)
				{
					_eric.movePower += 0.5;
					_eric.movePowerCount = 0;
				}
			}
			//==========���¿� ���� ���� 
			if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP || _eric.state == STATE_PUSH)
			{
				_eric.x -= _eric.movePower;
			}
			else if (_eric.state == STATE_PUSH)
			{
				// �ƹ��͵� �ƴϾ���� 
			}
			else
			{
				_eric.state = STATE_MOVE;
				_eric.x -= _eric.movePower;
			}
			// ���� �����̵� �̶�� �����̵� ���Ѷ� 
			if (_breathCount > 10 && _eric.state != STATE_PUSH) _isSlide = true;
		}
	}
	// ������ Ű�� ���������� ������ 
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//������ �ȼ� �浹 
		PixelRightCollision();
		if (_eric.state != STATE_PUSH)
		{
			_breathCount++;						 // ���� �ٸ� �� �̹����� ��Ÿ�� 
			//==========�̵� ���õ� �ڵ� =========//
			_eric.movePowerCount++;
			if (_eric.movePower <= 8)
			{
				if (_eric.movePowerCount > 4)
				{
					_eric.movePower += 0.5;
					_eric.movePowerCount = 0;
				}
			}
			//==========���¿� ���� ���� 
			if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP || _eric.state == STATE_PUSH)
			{
				_eric.x += _eric.movePower;
			}
			else if (_eric.state == STATE_PUSH)
			{
				// �ƹ��͵� �ƴϾ���� 
			}
			else
			{
				_eric.state = STATE_MOVE;
				_eric.x += _eric.movePower;	 // 0 �� ������ 
			}

			if (_breathCount > 10 && _eric.state != STATE_PUSH) _isSlide = true;
		}
	}

	//  �¿�Ű�� ���� 
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		// �� ī��Ʈ�� 150�̻��̸� �� ���� �̹����� ���� 
		if (_breathCount > 150)
		{
			_eric.state = STATE_BREATH;
			_eric.frameSpeed = 15;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(_eric.currentFrameX);
			_eric.movePower = 2;
			_breathCount = 0; // ��ī��Ʈ 
		}
		else // �� ī��Ʈ�� �ƴϸ� 
		{
			if (_eric.state == STATE_ERIC_HEADBUTT || _eric.state == STATE_ERIC_JUMP)
			{
				_eric.movePower = 2;
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
	//===============�����̵��� �ϱ� ���� ���� 
	if (_isSlide)
	{
		_slideCount++;
		if (_slideCount > 5)
		{
			_slideCount = 0;
			_isSlide = false;
		}
	}
	// ���� �����̵��� ������ 
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
	// ���� ���� 
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_eric.state = STATE_ERIC_HEADBUTT;
		_eric.frameSpeed = 6;
		_eric.currentFrameX = 0;
		_eric.image->setFrameX(0);
		_ericAttack = true;
	}
	// ���� ���� 
	if (!_ericJump)
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_ericJump = true;
			_eric.state = STATE_ERIC_JUMP;
			_eric.posState = POSSTATE_AIR; // �����̸� air
			_eric.jumpPower = 14;
			_eric.frameCount = 0;
			_eric.frameSpeed = 15;
			_eric.currentFrameX = 0;
			_eric.image->setFrameX(0);
			_jumpStart = _eric.y;
		}
	}


	// 191229 PM 03:18 �׽�Ʈ�� �̵�Ű �߰� (�����ؾ���)
	if (KEYMANAGER->isStayKeyDown('O'))
	{
		_eric.y -= 20;
	}
	if (KEYMANAGER->isStayKeyDown('L'))
	{
		_eric.y += 20;
	}
}

void playerEric::ericFrameCount()
{
	_eric.frameCount++; // ������ ī���� ���� 

	// ���°� ���� ���� ����
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
				_eric.frameSpeed = 15;
			}
			_eric.frameCount = 0;
		}
	}
	else if (_eric.state == STATE_ERIC_HEADBUTTEND)  // ��ġ�⸦ �� ���� 
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
	else if (_eric.state == STATE_ERIC_JUMP)   // ������ �� ���� 
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
	else  // �� �̿��� ���� 
	{
		if (_eric.frameCount >= _eric.frameSpeed)
		{
			_eric.currentFrameX++;
			_eric.image->setFrameX(_eric.currentFrameX);
	
			
			if (_eric.currentFrameX > _eric.image->getMaxFrameX())
			{
				//�״� ���¶�� 
				if (_eric.state == STATE_DIE ||
					_eric.state == STATE_MIRRA ||
					_eric.state == STATE_PRESSDIE ||
					_eric.state == STATE_POISON ||
					_eric.state == STATE_TRAPDIE)
				{
					_eric.isDead = true;
				}
				else
				{
					_eric.currentFrameX = 0;	
				}
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
		// ���� �ʱⰪ && �������̶�� 
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
//=============================���� ���� 
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
// ������ 
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

// ERIC�� ���� �� �Լ� 
void playerEric::ericHit()
{
	//���� �� ��Ʈ���� �������ּ� 
	if (_isHit)
	{
		_hitCount++;
		if (_eric.state != STATE_HIT)  _eric.state = STATE_HIT;
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
}
// ������ �̹����� �������ִ� �Լ� 
void playerEric::setEricImage()
{
	if (_eric.hp == 0)
	{
		_eric.state = STATE_DIE;
	}
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
		_eric.image = IMAGEMANAGER->findImage("eric_mirra");
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
//�ȼ� �浹 
void playerEric::PixelCollision()
{
	_eric.probeY = _eric.y + _eric.image->getFrameHeight();

	for (int i = _eric.probeY - 6; i < _eric.probeY + 10; ++i)
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
	_eric.probeX = _eric.x + _eric.image->getFrameWidth(); // _eric.right  

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
	_eric.probeX = _eric.x - 3;

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
		// ���� ���� �� ���ʾƷ� �𼭸� �ȼ� �浹 
		_eric.probeX = _eric.x - 3;

		COLORREF getPixel_AIR2 = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _eric.probeX, _eric.y + _eric.image->getFrameHeight());

		int r2 = GetRValue(getPixel_AIR2);
		int g2 = GetGValue(getPixel_AIR2);
		int b2 = GetBValue(getPixel_AIR2);

		if (!(r2 == 255 && g2 == 0 && b2 == 255))
		{
			if (_eric.posState == POSSTATE_AIR)
			{
			_eric.x = _eric.probeX + 8;
			}
		}
	
		// ���� ���� �� �����ʾƷ� �𼭸� �ȼ� �浹 
		_eric.probeX = _eric.x + _eric.image->getFrameWidth(); // _eric.right  

		COLORREF getPixel_AIR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _eric.probeX + 8, _eric.y + _eric.image->getFrameHeight());

		int r = GetRValue(getPixel_AIR);
		int g = GetGValue(getPixel_AIR);
		int b = GetBValue(getPixel_AIR);

		if (!(r == 255 && g == 0 && b == 255))
		{
			if (_eric.posState == POSSTATE_AIR)
			{
				_eric.x = _eric.probeX - _eric.image->getFrameWidth() - 8;
			}
		}


	// ���� ���� �� �ȼ� �浹 (Y��)
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

void playerEric::ericDie()
{
	if (_eric.hp == 0)
	{
		_eric.state == STATE_DIE;
	}
}
