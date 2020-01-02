#include "stdafx.h"
#include "Enemy.h"
#include"playerManager.h"

HRESULT Enemy::init(EnemyType enemyType, float x, float y)
{
	imageReset();
	//플레이어와 연동하는 함수
	
	//프레임 관련 변수 초기화
	_enemyState = EnemyState::IDLE;
	_frameX = _frameY = _frameCount = 0;
	switch (enemyType)
	{
	case EnemyType::MUMMY:
		_image = IMAGEMANAGER->findImage("Enemy_Mummy");
		_Attack_image = IMAGEMANAGER->findImage("Enemy_Mummy_Attack");
		_enemyAttackRect = RectMakeCenter(_x, _y, _image->getFrameWidth() * 2, _image->getFrameHeight());
		break;
	case EnemyType::SCORPION:
		_image = IMAGEMANAGER->findImage("Enemy_Scorpion");
		_Attack_image = IMAGEMANAGER->findImage("Enemy_Scorpion_Attack");
		_enemyAttackRect = RectMakeCenter(_x, _y, 600,200);
		break;
	case EnemyType::SNAKE:
		_image = IMAGEMANAGER->findImage("Enemy_Snake");
		_Attack_image = IMAGEMANAGER->findImage("Enemy_Snake_Attack");
		_enemyAttackRect = RectMakeCenter(_x, _y,600,200);
		break;
	case EnemyType::PLAYERMUMMY:
		_image = IMAGEMANAGER->findImage("Enemy_PlayerMummy");
		_Attack_image = IMAGEMANAGER->findImage("Enemy_PlayerMummy_Attack");
		_enemyAttackRect = RectMakeCenter(_x, _y, _image->getFrameWidth() * 2, _image->getFrameHeight());
		break;
	default:
		break;
	}
	_enemyHP = 4;

	_x = x;
	_y = y;

	_probeX = _x;
	_probeY = _y;

	_turn_Num = 0;
	_turn = false;

	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_enemy_DISCOVERY_Rect = RectMakeCenter(_x, _y, 600, 400);
	_cameraRect = RectMake(CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
	return S_OK;
}

void Enemy::release()
{

}

void Enemy::update()
{
	EnemyAction();		//적의 상태의 따른 행동을 지정하는 함수
	Frame();			//적의 프레임을 관리하는 함수
	if (_enemyHP <= 0)_enemyState = EnemyState::DIE;
	//playerLink();		//플레이어의 렉트를 받아오는 함수
	_enemyAttackRect = RectMakeCenter(_x, _y, _image->getFrameWidth() * 2, _image->getFrameHeight());
	_cameraRect = RectMake(CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
	_enemy_DISCOVERY_Rect = RectMakeCenter(_x, _y, 600, 400);
	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Enemy::render()
{
	//Rectangle(CAMERAMANAGER->getWorDC(), _enemy_DISCOVERY_Rect);
	if(KEYMANAGER->isToggleKey(VK_F1)) Rectangle(CAMERAMANAGER->getWorDC(), _enemyRect);
	_image->frameRender(CAMERAMANAGER->getWorDC(), _enemyRect.left, _enemyRect.top, _frameX, _frameY);
	//Rectangle(CAMERAMANAGER->getWorDC(), _ericRect);
	if(KEYMANAGER->isToggleKey(VK_F1)) Rectangle(CAMERAMANAGER->getWorDC(), _enemyRect);
	_image->frameRender(CAMERAMANAGER->getWorDC(), _enemyRect.left, _enemyRect.top, _frameX, _frameY);
	//Rectangle(CAMERAMANAGER->getWorDC(), _enemy_DISCOVERY_Rect);
	char buffer[128];
	Rectangle(CAMERAMANAGER->getWorDC(), _ericRect);
}

void Enemy::EnemyAction()
{
}

void Enemy::Frame()
{
	
}

void Enemy::Move()
{
	if (_turn_Num % 2 == 1)
	{
		_enemyLR = EnemyLR::LEFT;
		if (_frameX <= 3)
			_x -= 3;
	}
	else
	{
		_enemyLR = EnemyLR::RIGHT;
		if (_frameX <= 3)
			_x += 3;
	}
}

void Enemy::Scout()
{
	switch (_enemyLR)
	{
	case EnemyLR::LEFT:
		for (int i = _x - _image->getFrameWidth() / 2; i > _x - _image->getFrameWidth() / 2 - 70;--i)
		{
			//바닥에 색상을 구해온다
			COLORREF platformCOLOR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), i, _probeY + 50);
			//벽에 색상을 구해온다
			COLORREF wallCOLOR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), i, _y - _image->getFrameHeight());

			int wallR = GetRValue(wallCOLOR);
			int wallG = GetGValue(wallCOLOR);
			int wallB = GetBValue(wallCOLOR);

			int platformR = GetRValue(platformCOLOR);
			int platformG = GetGValue(platformCOLOR);
			int platformB = GetBValue(platformCOLOR);

			if (((platformR == 255 && platformG == 0 && platformB == 255) || (platformR == 255 && platformG == 255 && platformB == 255) || (platformR == 255 && platformG == 0 && platformB == 0) || (wallR == 255 && wallG == 255 && wallB == 0)) && !_turn)
			{
				_turn_Num++;
				_turn = true;
				break;
			}
			else
			{
				_turn = false;
				break;
			}
		}
		break;
	case EnemyLR::RIGHT:
		for (int i = _x + _image->getFrameWidth() / 2; i < _x + _image->getFrameWidth() / 2 + 70;++i)
		{
			//바닥에 색상을 구해온다
			COLORREF platformCOLOR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), i, _probeY + 50);
			//벽에 색상을 구해온다
			COLORREF wallCOLOR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), i, _y - _image->getFrameHeight());

			int wallR = GetRValue(wallCOLOR);
			int wallG = GetGValue(wallCOLOR);
			int wallB = GetBValue(wallCOLOR);

			int platformR = GetRValue(platformCOLOR);
			int platformG = GetGValue(platformCOLOR);
			int platformB = GetBValue(platformCOLOR);

			if (((platformR == 255 && platformG == 0 && platformB == 255) || (platformR == 255 && platformG == 255 && platformB == 255) || (platformR == 255 && platformG == 0 && platformB == 0) || (wallR == 255 && wallG == 255 && wallB == 0)) && !_turn)
			{
				_turn_Num++;
				_turn = true;
				break;
			}
			else
			{
				_turn = false;
				break;
			}
		}
		break;
	default:
		break;
	}
}

void Enemy::Discovery()
{
	RECT temp;
	switch (_enemyType)
	{
	case EnemyType::MUMMY:
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}

		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	case EnemyType::SCORPION:
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}

		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	case EnemyType::SNAKE:
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}

		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	case EnemyType::PLAYERMUMMY:
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}

		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::DISCOVERY;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	default:
		break;
	}
}
void Enemy::Tracking()
{
	RECT temp;
	switch (_discoveryPlayer)
	{
	case DISCOVERYPlayer::ERIC:
		//플레이어가 오른쪽에 있을때(에릭)
		if (_x < (_ericRect.left + _ericRect.right) / 2 && !_turn)
		{
			_turn = true;
			_enemyLR = EnemyLR::RIGHT;
			if (_frameX <= 3)
				_x += 3;
		}
		//플레이어가 왼쪽에 있을때(에릭)
		if (_x > (_ericRect.left + _ericRect.right) / 2 && !_turn)
		{
			_turn = true;
			_enemyLR = EnemyLR::LEFT;
			if (_frameX <= 3)
				_x -= 3;
		}
		if (!IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))_enemyState = EnemyState::SCOUT;		//플레이어(에릭)가 탐지범위 밖으로 나가면  SCOUT상태로 변함
		break;
	case DISCOVERYPlayer::BALEOG:
		//플레이어가 오른쪽에 있을때(벨로그)
		if (_x < (_baleogRect.left + _baleogRect.right) / 2 && !_turn)
		{
			_turn = true;
			_enemyLR = EnemyLR::RIGHT;
			if (_frameX <= 3)
				_x += 3;
		}
		//플레이어가 왼쪽에 있을때(벨로그)
		if (_x > (_baleogRect.left + _baleogRect.right) / 2 && !_turn)
		{
			_turn = true;
			_enemyLR = EnemyLR::LEFT;
			if (_frameX <= 3)
				_x -= 3;
		}
		break;
		if (!IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))_enemyState = EnemyState::SCOUT;	//플레이어(벨로그)가 탐지범위 밖으로 나가면  SCOUT상태로 변함
	case DISCOVERYPlayer::OLAF:
		//플레이어가 오른쪽에 있을때(올라프)
		if (_x < (_olafRect.left + _olafRect.right) / 2 && !_turn)
		{
			_turn = true;
			_enemyLR = EnemyLR::RIGHT;
			if (_frameX <= 3)
				_x += 3;
		}
		//플레이어가 왼쪽에 있을때(올라프)
		if (_x > (_olafRect.left + _olafRect.right) / 2 && !_turn)
		{
			_turn = true;
			_enemyLR = EnemyLR::LEFT;
			if (_frameX <= 3)
				_x -= 3;
		}
		if (!IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))_enemyState = EnemyState::SCOUT;		//플레이어(올라프)가 탐지범위 밖으로 나가면  SCOUT상태로 변함
		break;
	default:
		break;
	}



	Scout();
	//Move();
}
void Enemy::Attack(EnemyType enemyType)
{
	RECT temp;
	switch (enemyType)
	{
	case EnemyType::MUMMY:
		if (IntersectRect(&temp, &_enemyAttackRect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	case EnemyType::SCORPION:
		if (IntersectRect(&temp, &_enemyAttackRect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	case EnemyType::SNAKE:
		if (IntersectRect(&temp, &_enemyAttackRect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	case EnemyType::PLAYERMUMMY:
		if (IntersectRect(&temp, &_enemyAttackRect, &_ericRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::ERIC;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_olafRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::OLAF;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		if (IntersectRect(&temp, &_enemyAttackRect, &_baleogRect))
		{
			_discoveryPlayer = DISCOVERYPlayer::BALEOG;
			_enemyState = EnemyState::ATTACK;	//플레이어를 발견하면 DISCOVERY상태로 변함
		}
		break;
	default:
		break;
	}
}

void Enemy::Attack()
{
}

void Enemy::setPlayerRect(RECT eric, RECT baleog, RECT olaf)
{
	_ericRect = eric;
	_baleogRect = baleog;
	_olafRect = olaf;
}

void Enemy::platformColision()
{
	//적을 바닥에 붙여주기 위함
	for (int i = _probeY; i < _probeY + 100; ++i)
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

HRESULT Enemy_Bullet::init()
{

	return S_OK;
}

void Enemy_Bullet::release()
{
}

void Enemy_Bullet::update()
{
}

void Enemy_Bullet::render()
{
}

void Enemy_Bullet::bulletFire(float x, float y, float angle)
{
	_x = x;
	_y = y;
	_angle = angle;


}

void Enemy_Bullet::bulletMove()
{

}