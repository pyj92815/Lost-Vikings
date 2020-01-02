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
		break;
	case EnemyType::SCORPION:
		_image = IMAGEMANAGER->findImage("Enemy_Scorpion");
		break;
	case EnemyType::SNAKE:
		_image = IMAGEMANAGER->findImage("Enemy_Snake");
		break;
	case EnemyType::PLAYERMUMMY:
		_image = IMAGEMANAGER->findImage("Enemy_PlayerMummy");
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
	EnemyAction();		//적의 상태의 따른 행동을 지정하는 함수
	Frame();			//적의 프레임을 관리하는 함수

	//playerLink();		//플레이어의 렉트를 받아오는 함수

	_cameraRect = RectMake(CAMERAMANAGER->get_Camera_X(), CAMERAMANAGER->get_Camera_Y(), CAMERAMANAGER->get_CameraSizeX(), CAMERAMANAGER->get_CameraSizeY());
	_enemy_DISCOVERY_Rect = RectMakeCenter(_x, _y, 600, 400);
	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Enemy::render()
{
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

void Enemy::setPlayerRect(RECT eric, RECT baleog, RECT olaf)
{
	_ericRect = eric;
	_baleogRect = baleog;
	_olafRect = olaf;
}