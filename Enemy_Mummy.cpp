#include "stdafx.h"
#include "Enemy_Mummy.h"

void Enemy_Mummy::EnemyAction()
{
	_probeY = _y + _image->getFrameHeight() / 2;
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		RECT temp;
		//카메라 안으로 들어가면 SCOUT상태로 변함
		if (IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::SCOUT;
		break;
	case EnemyState::SCOUT:
		
		Scout();				//움직이다 절벽/벽 을 만나면 반대편으로 돌아가도록 하는 함수
		Move();					//좌우로 움직이게 하는 함수
		
		Discovery();

		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//카메라 밖으로 나가면 IDLE상태로 변함
		break;
	case EnemyState::DISCOVERY:
		Tracking();
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//카메라 밖으로 나가면 IDLE상태로 변함
		break;
	case EnemyState::ATTACK:
		//이미지 = 공격 이미지로 바꾸고
		//if(공격 판정이 있을만한 이미지에 플레이어가 닿으면 플레이어 사망)
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

void Enemy_Mummy::Frame()
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
