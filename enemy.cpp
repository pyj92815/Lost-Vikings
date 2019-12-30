#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(EnemyType enemyType,float x,float y)
{
	imageReset();
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
	//_image = IMAGEMANAGER->findImage("Enemy_Mummy");
	_x = x;
	_y = y;
	_rect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void Enemy::release()
{

}

void Enemy::update()
{
	EnemyAction();
}

void Enemy::render()
{
	Rectangle(CAMERAMANAGER->getWorDC(), _rect);
	_image->frameRender(CAMERAMANAGER->getWorDC(), _rect.left, _rect.top);
}

void Enemy::EnemyAction()
{

}

void Enemy::EnemyCreate(float x, float y)
{
	/*switch (enemyType)
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
	}*/
	_image= IMAGEMANAGER->findImage("Enemy_Mummy");
	_x = x;
	_y = y;
	_rect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}
