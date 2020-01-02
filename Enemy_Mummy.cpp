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

		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))
		{
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
			_playerRect = _ericRect;
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))
		{
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
			_playerRect = _olafRect;
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))
		{
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
			_playerRect = _baleogRect;
		}

		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//카메라 밖으로 나가면 IDLE상태로 변함
		break;
	case EnemyState::DISCOVERY:
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))
		{
			_playerRect = _ericRect;
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))
		{
			_playerRect = _olafRect;
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))
		{
			_playerRect = _baleogRect;
		}
		_player.x = (_playerRect.left + _playerRect.right) / 2;
		if (_x < _player.x)
		{
			_enemyLR = EnemyLR::RIGHT;
			if (_frameX <= 3)
				_x += 3;
		}
		if(_x>_player.x)
		{
			_enemyLR = EnemyLR::LEFT;
			if (_frameX <= 3)
				_x -= 3;
		}
		Scout();
		//Move();

		if (!IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_playerRect))_enemyState = EnemyState::SCOUT;
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//카메라 밖으로 나가면 IDLE상태로 변함
		break;
	case EnemyState::ATTACK:
		//이미지 = 공격 이미지로 바꾸고
		//if(공격 판정이 있을만한 이미지에 플레이어가 닿으면 플레이어 사망)
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

	//적을 바닥에 붙여주기 위함
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
