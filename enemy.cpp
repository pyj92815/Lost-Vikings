#include "stdafx.h"
#include "Enemy.h"
#include"playerManager.h"
HRESULT Enemy::init(EnemyType enemyType, float x, float y)
{
	imageReset();
	_playerManager = new playerManager;
	//프레임 관련 변수 초기화
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
	EnemyAction();
	Frame();
	_cameraRect = RectMake(CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
	_enemy_DISCOVERY_Rect = RectMakeCenter(_x, _y, 600, 400);
	//_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Enemy::render()
{
	Rectangle(CAMERAMANAGER->getWorDC(), _enemyRect);
	_image->frameRender(CAMERAMANAGER->getWorDC(), _enemyRect.left, _enemyRect.top, _frameX, _frameY);
	Rectangle(CAMERAMANAGER->getWorDC(), _enemy_DISCOVERY_Rect);

}

void Enemy::EnemyAction()
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
			
		Scout();			//움직이다 절벽/벽 을 만나면 반대편으로 돌아가도록 하는 함수
		Move();				//좌우로 움직이게 하는 함수

		//카메라 밖으로 나가면 IDLE상태로 변함
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;
		//if(적을 발견하면(적이 렉트 범위 안에 들어오면))_enemyState=EnemyState::DISCOVERY;
		break;
	case EnemyState::DISCOVERY:
		//적을 추적
		//if(_x>player.x)_x-=
		//if(_x<_player.x)_x+=
		//if(플레이어의 렉트가 공격범위 렉트안에 들어오면)_enemyState=EnemyState::ATTACK;
		//else if(적이 탐색 범위 밖으로 나가면)_enemyState=EnemyState::SCOUT;
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
