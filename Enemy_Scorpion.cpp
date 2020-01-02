#include "stdafx.h"
#include "Enemy_Scorpion.h"

void Enemy_Scorpion::EnemyAction()
{
	_probeY = _y + _image->getFrameHeight() / 2;

	switch (_enemyState)
	{
	case EnemyState::IDLE:
		RECT temp;
		//ī�޶� ������ ���� SCOUT���·� ����
		if (IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::SCOUT;
		break;
	case EnemyState::SCOUT:
	
		Scout();				//�����̴� ����/�� �� ������ �ݴ������� ���ư����� �ϴ� �Լ�
		Move();					//�¿�� �����̰� �ϴ� �Լ�
		
		//ī�޶� ������ ������ IDLE���·� ����
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;
		//if(���� �߰��ϸ�(���� ��Ʈ ���� �ȿ� ������))_enemyState=EnemyState::DISCOVERY;
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

	//���� �ٴڿ� �ٿ��ֱ� ����
	for (int i = _probeY - 20; i < _probeY + 200; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _x, i);

		int r = GetRValue(getPixel_Bottom);
		int g = GetGValue(getPixel_Bottom);
		int b = GetBValue(getPixel_Bottom);

		if (r == 255 && g == 255 && b == 0)
		{
			_y = i - _image->getFrameHeight() / 2;
			break;
		}
	}

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
