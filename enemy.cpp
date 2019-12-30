#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(EnemyType enemyType,float x,float y)
{
	imageReset();
	//������ ���� ���� �ʱ�ȭ
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
	//_image = IMAGEMANAGER->findImage("Enemy_Mummy");
	_x = x;
	_y = y;
	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
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
	Rectangle(CAMERAMANAGER->getWorDC(), _enemyRect);
	_image->frameRender(CAMERAMANAGER->getWorDC(), _enemyRect.left, _enemyRect.top);
}

void Enemy::EnemyAction()
{
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		//if(ī�޶� �ȿ� ������)_enemyState=EnemyState::SCOUT;
		break;
	case EnemyState::SCOUT:
		//�¿�� �����̴�
		//if(���� �߰��ϸ�(���� ��Ʈ ���� �ȿ� ������))_enemyState=EnemyState::DISCOVERY;
		break;
	case EnemyState::DISCOVERY:
		//���� ����
		//if(_x>player.x)_x-=
		//if(_x<_player.x)_x+=
		//if(�÷��̾��� ��Ʈ�� ���ݹ��� ��Ʈ�ȿ� ������)_enemyState=EnemyState::ATTACK;
		break;
	case EnemyState::ATTACK:
		//�̹��� = ���� �̹����� �ٲٰ�
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

	_enemyRect = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}