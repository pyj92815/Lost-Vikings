#include "stdafx.h"
#include "Enemy_PlayerMummy.h"

void Enemy_PlayerMummy::EnemyAction()
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

		Discovery();			//���� �߰��ϴ� �Լ�
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//ī�޶� ������ ������ IDLE���·� ����
		break;
	case EnemyState::DISCOVERY:
		Tracking();				//���� �Ѵ� �Լ�
		Attack();				//���� ���ݹ����ȿ� ���ý� _enemyState�� ATTACK�� �������ִ� �Լ�
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//ī�޶� ������ ������ IDLE���·� ����
		break;
	case EnemyState::ATTACK:
		UnAttack();				//���ݹ��� ������ ������ SCOUT
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//ī�޶� ������ ������ IDLE���·� ����
		break;
	case EnemyState::DIE:

		_die = true;
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

	platformColision();
}

void Enemy_PlayerMummy::Frame()
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
		_frameCount++;
		if (_frameCount >= 10)
		{
			_frameX++;
			if (_frameX > 5)
				_frameX = 0;
			_frameCount = 0;
		}
		break;
	case EnemyState::DIE:
		break;
	default:
		break;
	}
}