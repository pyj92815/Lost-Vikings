#include "stdafx.h"
#include "Enemy_Snake.h"



void Enemy_Snake::EnemyAction()
{
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		RECT temp;
		//카메로 안으로 들어오면 _enemyState를 SCOUT로 바꿈
		if (IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::SCOUT;
		break;
	case EnemyState::SCOUT:
		Discovery();			//적을 발견하는 함수
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

void Enemy_Snake::Frame()
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
			if (_frameX > 1)
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