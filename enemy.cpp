#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(EnemyType enemyType, float x, float y)
{
	imageReset();
	//������ ���� ���� �ʱ�ȭ
	_enemyState = EnemyState::IDLE;
	_frameX = _frameY = _frameCount = 0;
	switch (enemyType)
	{
	case EnemyType::MUMMY:
		_image = IMAGEMANAGER->findImage("Enemy_Mummy");
		break;
	case EnemyType::SCORPION:
		_image = IMAGEMANAGER->findImage("Enemy_Scorpion");
		break;
	case EnemyType::SNAKE:
		_image = IMAGEMANAGER->findImage("Enemy_Snake");
		break;
	default:
		break;
	}
	
	_x = x;
	_y = y;
	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_cameraRect = RectMake(CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
	return S_OK;
}

void Enemy::release()
{

}

void Enemy::update()
{
	EnemyAction();
	Frame();
	_cameraRect = RectMake(CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Enemy::render()
{
	Rectangle(CAMERAMANAGER->getWorDC(), _enemyRect);
	_image->frameRender(CAMERAMANAGER->getWorDC(), _enemyRect.left, _enemyRect.top, _frameX, _frameY);
	//Rectangle(CAMERAMANAGER->getWorDC(), _cameraRect);
	
}

void Enemy::EnemyAction()
{
	int probeY = _y + _image->getFrameHeight() / 2 + 20;
	int probeX = _x;
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		RECT temp;
		//ī�޶� ������ ���� SCOUT���·� ����
		if (IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::SCOUT;
		break;
	case EnemyState::SCOUT:
		//probeY,X ���� �̿��� ������ ������ �ݴ������� ���ư���
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;

		//�¿�� �����̴�
		//if(���� �߰��ϸ�(���� ��Ʈ ���� �ȿ� ������))_enemyState=EnemyState::DISCOVERY;
		//else if(ī�޶� ������ ������)_enemyState=EnemyState::IDLE;
		break;
	case EnemyState::DISCOVERY:
		//���� ����
		//if(_x>player.x)_x-=
		//if(_x<_player.x)_x+=
		//if(�÷��̾��� ��Ʈ�� ���ݹ��� ��Ʈ�ȿ� ������)_enemyState=EnemyState::ATTACK;
		//else if(���� Ž�� ���� ������ ������)_enemyState=EnemyState::SCOUT;
		break;
	case EnemyState::ATTACK:
		//�̹��� = ���� �̹����� �ٲٰ�
		//if(���� ������ �������� �̹����� �÷��̾ ������ �÷��̾� ���)
		break;
	case EnemyState::DIE:

		break;
	default:
		break;
	}

	switch (_enemyLR)
	{
	case EnemyLR::LEFT:
		_frameY = 1;
		break;
	case EnemyLR::RIGHT:
		_frameY = 0;
		break;
	default:
		break;
	}

	_probeY = _y+_image->getFrameHeight()/2;
	for (int i = _probeY-20; i < _probeY+200; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_enemyRect.left + _enemyRect.right) / 2, i);

		int r = GetRValue(getPixel_Bottom);
		int g = GetGValue(getPixel_Bottom);
		int b = GetBValue(getPixel_Bottom);

		if (r == 255 && g == 255&&b==0)
		{
			_y = i-_image->getFrameHeight()/2;
			break;
		}
	}
	
}

void Enemy::turn()
{
	if (_enemyLR == EnemyLR::LEFT)
	{
		_enemyLR = EnemyLR::RIGHT;
	}
	else
	{
		_enemyLR = EnemyLR::LEFT;
	}
}

void Enemy::Frame()
{
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		_frameCount = 0;
		_frameX = 0;
		break;
	case EnemyState::SCOUT:
		_frameCount++;
		if (_frameCount >= 10)
		{
			_frameX++;
			if (_frameX > 5)
				_frameX = 0;
			_frameCount = 0;
		}
		break;
	case EnemyState::DISCOVERY:
		_frameCount++;
		if (_frameCount >= 10)
		{
			_frameX++;
			if (_frameX > 5)
				_frameX = 0;
			_frameCount = 0;
		}
		break;
	case EnemyState::ATTACK:
		break;
	case EnemyState::DIE:
		break;
	default:
		break;
	}
}

void Enemy::proveLeft()
{
	for (int i = _probeX;i < _probeX + _image->getFrameWidth() / 2;++i)
	{
		COLORREF COLOR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), i, _probeY);

		int r = GetRValue(COLOR);
		int g = GetGValue(COLOR);
		int b = GetBValue(COLOR);

		if (r == 255 && g == 255 && b == 0)
		{
			_turn = true;
			break;
		}
		else
		{
			_turn = false;
			break;
		}
	}
}

void Enemy::proveRight()
{
	for (int i = _probeX;i > _probeX - _image->getFrameWidth() / 2;--i)
	{
		COLORREF COLOR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), i, _probeY);

		int r = GetRValue(COLOR);
		int g = GetGValue(COLOR);
		int b = GetBValue(COLOR);

		if (r == 255 && g == 255 && b == 0)
		{
			_turn = false;
			break;
		}
		else
		{
			_turn = true;
			break;
		}
	}
}
