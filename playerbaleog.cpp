#include "stdafx.h"
#include "playerbaleog.h"


playerbaleog::playerbaleog()
{
}

playerbaleog::~playerbaleog()
{
}

HRESULT playerbaleog::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("���αױ⺻", "./image/Characters/baleog_idel_x3.bmp", 156, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���α��̵�", "./image/Characters/baleog_move_x3.bmp", 744, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���α�Į1", "./image/Characters/baleog_sword1_x3.bmp", 444, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���α�Į2", "./image/Characters/baleog_sword2_x3.bmp", 444, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ȭ���غ�", "./image/Characters/baleog_arrow1_x3.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ȭ��߻�", "./image/Characters/baleog_arrow2_x3.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�б�", "./image/Characters/baleog_push_x3.bmp", 372, 198, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "./image/Characters/baleog_die_x3.bmp", 768, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "./image/Characters/baleog_air_x3.bmp", 168, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "./image/Characters/baleog_poison_x3.bmp", 186, 198, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�л�", "./image/Characters/baleog_pressdie_x3.bmp", 279, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�̶��", "./image/Characters/baleog_mirra_x3.bmp", 216, 186, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����", "./image/Characters/baleog_trapdie_x3.bmp", 288, 180, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ٸ��̵�", "./image/Characters/baleog_ladder_x3.bmp", 321, 192, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ٸ�����", "./image/Characters/bakeog_ladder_end_x3.bmp", 186, 192, 2, 1, true, RGB(255, 0, 255));

	_baleog.image = IMAGEMANAGER->findImage("���αױ⺻");
	_baleog.image->setFrameY(0);
	_baleog.currentFrameX = _baleog.currentFrameY = 0;
	_baleog.state = STATE_IDLE;
	_baleog.posState = POSSTATE_GROUND;
	_baleog.x = x;
	_baleog.y = y;
	_baleog.hp = 3;
	_baleog.frameSpeed = 10;
	_baleog.frameCount = 0;
	_baleog.rc = RectMake(_baleog.x, _baleog.y, _baleog.image->getFrameWidth(), _baleog.image->getFrameHeight());
	_baleog.currentFrameX = _baleog.currentFrameY = 0;
	_baleogAttackMotion = false;
	_baleogAttack = false;
	_baleogAttackCount = 0;

	//ȭ��
	_ar = new arrow;
	_ar->init(300, 800);



	return S_OK;
}

void playerbaleog::release()
{
}

void playerbaleog::update()
{

	// ����̵�Ű
	//if (!_baleogAttack) hgKey();

	// â�Բ� �̵� �ڵ����� �����̰� ���� ������
	 if (!_baleogAttack) key();

	_baleog.rc = RectMake(_baleog.x, _baleog.y, _baleog.image->getFrameWidth(), _baleog.image->getFrameHeight());

	setBaleogState();

	//������ȸ��
	_baleog.frameCount++;


	//�̱��� 
	if (_baleog.state == STATE_BALEOG_SWORD1 || _baleog.state == STATE_BALEOG_SWORD2)
	{
		_baleog.frameCount++;
		if (_baleog.frameCount > _baleog.frameSpeed)
		{
			_baleog.currentFrameX++;
			_baleog.image->setFrameX(_baleog.currentFrameX);

			if (_baleog.image->getMaxFrameX() < _baleog.currentFrameX)
			{
				if (_baleog.state == STATE_BALEOG_SWORD1)
				{
					_baleogAttackMotion = true;
				}
				else
				{
					_baleogAttackMotion = false;
				}
				_baleog.state = STATE_IDLE;
				_baleog.currentFrameX = 0;
				_baleog.image->setFrameX(_baleog.currentFrameX);
				_baleogAttack = false;

			}
			_baleog.frameCount = 0;
		}
	}

	if (_baleog.state == STATE_BALEOG_ARROW_REDY)
	{
		_baleog.frameCount++;
		if (_baleog.frameCount >= _baleog.frameSpeed)
		{
			_baleog.image->setFrameX(_baleog.currentFrameX);
			//_baleog.currentFrameX++;

			if (_baleog.image->getMaxFrameX() > _baleog.currentFrameX) _baleog.currentFrameX++;

			if (_baleog.image->getMaxFrameX() < _baleog.currentFrameX)
			{/*
				if(_baleog.state == STATE_BALEOG_ARROW_REDY)*/
				//_baleog.currentFrameX = 3;
				ss = false;
			}
			_baleog.frameCount = 0;
		}
	}
	else
	{
		_baleog.frameCount++;
		if (_baleog.frameCount > _baleog.frameSpeed)	//������ī��Ʈ > �����ӽ��ǵ� ��
		{
			_baleog.currentFrameX++;
			_baleog.image->setFrameX(_baleog.currentFrameX);

			if (_baleog.image->getMaxFrameX() < _baleog.currentFrameX)
			{

				_baleog.currentFrameX = 0;

			}
			_baleog.frameCount = 0;
		}
	}


	/*if (_count % 2 == 0 && _move.type != MT_BOSS &&
		_move.type != MT_BOSS2)
		if(_count % 2 == 0)
	{
		if (_baleog.currentFrameX >= _baleog.image->getMaxFrameX()) _baleog.currentFrameX = 0;

		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;
		_count = 0;
	}
*/
	CAMERAMANAGER->set_Camera_XY(_baleog.rc);

	_ar->update();

}

void playerbaleog::render()
{
	Rectangle(getMemDC(), _baleog.rc);
	_baleog.image->frameRender(CAMERAMANAGER->getWorDC(), _baleog.x, _baleog.y, _baleog.currentFrameX, _baleog.currentFrameY);



	_ar->render();

}

void playerbaleog::key()
{
	//�̵�
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_baleog.state = STATE_MOVE;
		_baleog.x += 3;
		_baleog.currentFrameY = 0;

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_baleog.state = STATE_MOVE;
		_baleog.x -= 3;
		_baleog.currentFrameY = 1;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_baleog.state = STATE_IDLE;
		_baleog.currentFrameX = 0;
		_baleog.image->setFrameX(_baleog.currentFrameX);
		_baleog.frameCount = 0;
	}

	////�̵�Ű ����ó��
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_baleog.state == STATE_MOVE)
			_baleog.state = STATE_IDLE;
		_baleog.image->setFrameY(0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if ((_baleog.state == STATE_MOVE && _baleog.currentFrameY == 1) ||
			(_baleog.state == STATE_BALEOG_SWORD1 && _baleog.currentFrameY == 1))
			_baleog.state = STATE_IDLE;
		_baleog.image->setFrameY(1);
	}



	//����Ű
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_baleogAttack = true;
		if (!_baleogAttackMotion)
		{
			_baleog.state = STATE_BALEOG_SWORD1;
		}
		else
		{
			_baleog.state = STATE_BALEOG_SWORD2;
		}
		/*_baleog.currentFrameX = 0;*/
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_baleog.state = STATE_BALEOG_ARROW_REDY;
		if (!ss)
		{
			/*_baleog.currentFrameX = 0; */
			ss = true;
		}
	}

	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_baleog.state = STATE_BALEOG_ARROW_FIRE;
		_baleog.currentFrameX = 0;

		_ar->fire(_baleog.x + _baleog.image->getFrameWidth() / 2,
			_baleog.y + _baleog.image->getFrameHeight() / 2, 10.f, _baleog.currentFrameY * PI, _baleog.currentFrameY);

	}
}

void playerbaleog::setBaleogState()
{
	switch (_baleog.state)
	{
	case STATE_IDLE:
		_baleog.image = IMAGEMANAGER->findImage("���αױ⺻");
		break;
	case STATE_MOVE:
		_baleog.image = IMAGEMANAGER->findImage("���α��̵�");
		break;
	case STATE_ERIC_JUMP:
		break;
	case STATE_ERIC_HEADBUTT:
		break;
	case STATE_OLAF_GUARD:
		break;
	case STATE_OLAF_FLY:

		break;
	case STATE_BALEOG_ARROW_REDY:
		_baleog.image = IMAGEMANAGER->findImage("ȭ���غ�");
		break;
	case STATE_BALEOG_ARROW_FIRE:
		_baleog.image = IMAGEMANAGER->findImage("ȭ��߻�");
		break;
	case STATE_BALEOG_SWORD1:
		_baleog.image = IMAGEMANAGER->findImage("���α�Į1");
		break;
	case STATE_BALEOG_SWORD2:
		_baleog.image = IMAGEMANAGER->findImage("���α�Į2");
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

void playerbaleog::hgKey()
{
	//�̵�

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5))
	{
		_baleog.state = STATE_MOVE;
		_baleog.y -= 3;
		_baleog.currentFrameY = 0;

	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD2))
	{
		_baleog.state = STATE_MOVE;
		_baleog.y += 3;
		_baleog.currentFrameY = 0;

	}

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD3))
	{
		_baleog.state = STATE_MOVE;
		_baleog.x += 3;
		_baleog.currentFrameY = 0;

	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1))
	{
		_baleog.state = STATE_MOVE;
		_baleog.x -= 3;
		_baleog.currentFrameY = 1;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD3) || KEYMANAGER->isOnceKeyUp(VK_NUMPAD1))
	{
		_baleog.state = STATE_IDLE;
		_baleog.currentFrameX = 0;
		_baleog.image->setFrameX(_baleog.currentFrameX);
		_baleog.frameCount = 0;
	}

	////�̵�Ű ����ó��
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD3))
	{
		if (_baleog.state == STATE_MOVE)
			_baleog.state = STATE_IDLE;
		_baleog.image->setFrameY(0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD1))
	{
		if ((_baleog.state == STATE_MOVE && _baleog.currentFrameY == 1) ||
			(_baleog.state == STATE_BALEOG_SWORD1 && _baleog.currentFrameY == 1))
			_baleog.state = STATE_IDLE;
		_baleog.image->setFrameY(1);
	}



	//����Ű
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		_baleogAttack = true;
		if (!_baleogAttackMotion)
		{
			_baleog.state = STATE_BALEOG_SWORD1;
		}
		else
		{
			_baleog.state = STATE_BALEOG_SWORD2;
		}
		/*_baleog.currentFrameX = 0;*/
	}

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6))
	{
		_baleog.state = STATE_BALEOG_ARROW_REDY;
		if (!ss)
		{
			/*_baleog.currentFrameX = 0; */
			ss = true;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_NUMPAD6))
	{
		_baleog.state = STATE_BALEOG_ARROW_FIRE;
		_baleog.currentFrameX = 0;

		_ar->fire(_baleog.x + _baleog.image->getFrameWidth() / 2,
			_baleog.y + _baleog.image->getFrameHeight() / 2, 10.f, _baleog.currentFrameY * PI, _baleog.currentFrameY);

	}
}


HRESULT arrow::init(int arrowMax, float range)
{
	_arrowMax = arrowMax;
	_range = range;
	return S_OK;
}

void arrow::release()
{
}

void arrow::update()
{
	arrowMove(0);
}

void arrow::render()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end(); ++_viArrow)
	{
		_viArrow->arrowImage->frameRender(CAMERAMANAGER->getWorDC(),
			_viArrow->rc.left,
			_viArrow->rc.top,
			_viArrow->arrowImage->getFrameX(), _viArrow->direction);

		_viArrow->count++;
		if (_viArrow->count % 5 == 0)
		{
			_viArrow->arrowImage->setFrameX(_viArrow->arrowImage->getFrameX() + 1);
			if (_viArrow->arrowImage->getFrameX() >= _viArrow->arrowImage->getMaxFrameX())
			{
				_viArrow->arrowImage->setFrameX(0);
			}

			_viArrow->count = 0;

		}
	}
}

void arrow::fire(float x, float y, float speed, float angle, int direction)
{

	if (_arrowMax < _vArrow.size())return;
	tagArrow arrow;
	ZeroMemory(&arrow, sizeof(arrow));

	arrow.arrowImage = new image;
	arrow.arrowImage->init("./image/Characters/ȭ��1.bmp", 0, 0, 96, 28, 3, 2, true, RGB(255, 0, 255));
	arrow.speed = speed;
	arrow.angle = angle;
	arrow.x = arrow.fireX = x;
	arrow.y = arrow.fireY = y;
	arrow.rc = RectMakeCenter(arrow.x, arrow.y,
		arrow.arrowImage->getFrameWidth(),
		arrow.arrowImage->getFrameHeight());
	arrow.direction = direction;

	_vArrow.push_back(arrow);
}

void arrow::removeArrow(int arrNum)
{
	_vArrow[arrNum].arrowImage->release();
	_vArrow.erase(_vArrow.begin() + arrNum);
}

void arrow::arrowMove(bool fire)
{
	if (fire == 0)
	{
		for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
		{
			_viArrow->x += _viArrow->speed * cos(_viArrow->angle);
			_viArrow->y -= _viArrow->speed * sin(_viArrow->angle);

			_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y,
				_viArrow->arrowImage->getFrameWidth(),
				_viArrow->arrowImage->getFrameHeight());
			if (_range < getDistance(_viArrow->x, _viArrow->y, _viArrow->fireX,
				_viArrow->fireY))
			{
				SAFE_RELEASE(_viArrow->arrowImage);
				SAFE_DELETE(_viArrow->arrowImage);
				_viArrow = _vArrow.erase(_viArrow);
			}
			else ++_viArrow;

		}

	}
}
