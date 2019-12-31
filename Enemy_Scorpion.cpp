#include "stdafx.h"
#include "Enemy_Scorpion.h"

void Enemy_Scorpion::EnemyAction()
{
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		RECT temp;
		if (IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::SCOUT;
		break;
	case EnemyState::SCOUT:
		//_probeY = _enemyRect.bottom;
		//_x += 2;
		//�¿�� �����̴�
		//if(���� �߰��ϸ�(���� ��Ʈ ���� �ȿ� ������))_enemyState=EnemyState::DISCOVERY;

		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;
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

	_probeY = _y + _image->getFrameHeight() / 2;
	for (int i = _probeY; i < _probeY + 200; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_enemyRect.left + _enemyRect.right) / 2, i);

		int r = GetRValue(getPixel_Bottom);
		int g = GetGValue(getPixel_Bottom);
		int b = GetBValue(getPixel_Bottom);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _image->getFrameHeight() / 2;
			break;
		}
	}
	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Enemy_Scorpion::Frame()
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
			if (_frameX > 3)
				_frameX = 0;
			_frameCount = 0;
		}

		break;
	case EnemyState::DISCOVERY:
		break;
	case EnemyState::ATTACK:
		break;
	case EnemyState::DIE:
		break;
	default:
		break;
	}
}
