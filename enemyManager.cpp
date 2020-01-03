#include "stdafx.h"
#include "EnemyManager.h"
#include"playerManager.h"
#include "enemy.h"


EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	_enemyBullet = new Enemy_Bullet;
	_enemyBullet->init();
	_worldObjects = new worldObjects;
	_worldObjects->init();
	EnemyCreate();
	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->update();
		(*_viEnemy)->setPlayerRect(_playerManager->getPlayerEric().rc, _playerManager->getPlayerBaleog().rc, _playerManager->getPlayerOlaf().rc);
	}
	_enemyBullet->update();
	_ericRect = _playerManager->getPlayerEric().rc;
	_baleogRect = _playerManager->getPlayerBaleog().rc;
	_olafRect = _playerManager->getPlayerOlaf().rc;

	EnemyRemove();
	bulletFire();
	Collision();
}

void EnemyManager::render()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->render();
	}
	_enemyBullet->render();

}

void EnemyManager::EnemyCreate()
{
	Enemy* Mummy_1;
	Mummy_1 = new Enemy_Mummy;
	Mummy_1->init(EnemyType::MUMMY, 83, 750);
	_vEnemy.push_back(Mummy_1);

	Enemy* Mummy_2;
	Mummy_2 = new Enemy_Mummy;
	Mummy_2->init(EnemyType::MUMMY, 2380, 270);
	_vEnemy.push_back(Mummy_2);

	Enemy* Mummy_3;
	Mummy_3 = new Enemy_Mummy;
	Mummy_3->init(EnemyType::MUMMY, 3180, 185);
	_vEnemy.push_back(Mummy_3);

	Enemy* Mummy_4;
	Mummy_4 = new Enemy_Mummy;
	Mummy_4->init(EnemyType::MUMMY, 3710, 955);
	_vEnemy.push_back(Mummy_4);


	Enemy* Mummy_5;
	Mummy_5 = new Enemy_Mummy;
	Mummy_5->init(EnemyType::MUMMY, 3390, 1240);
	_vEnemy.push_back(Mummy_5);

	//Enemy* Scorpion_1;
	//Scorpion_1 = new Enemy_Scorpion;
	//Scorpion_1->init(EnemyType::SCORPION, 1440, 375);
	//_vEnemy.push_back(Scorpion_1);

	//Enemy* Scorpion_2;
	//Scorpion_2 = new Enemy_Scorpion;
	//Scorpion_2->init(EnemyType::SCORPION, 2063, 950);
	//_vEnemy.push_back(Scorpion_2);

	//Enemy* Scorpion_3;
	//Scorpion_3 = new Enemy_Scorpion;
	//Scorpion_3->init(EnemyType::SCORPION, 3246, 1245);
	//_vEnemy.push_back(Scorpion_3);

	Enemy* Snake_1;
	Snake_1 = new Enemy_Snake;
	Snake_1->init(EnemyType::SNAKE, 1100, 380);
	_vEnemy.push_back(Snake_1);

	Enemy* Snake_2;
	Snake_2 = new Enemy_Snake;
	Snake_2->init(EnemyType::SNAKE, 2515, 615);
	_vEnemy.push_back(Snake_2);

	Enemy* Snake_3;
	Snake_3 = new Enemy_Snake;
	Snake_3->init(EnemyType::SNAKE, 2751, 615);
	_vEnemy.push_back(Snake_3);
}

void EnemyManager::EnemyCreate(float x, float y)
{
	Enemy* PlayerMummy;
	PlayerMummy = new Enemy_PlayerMummy;
	PlayerMummy->init(EnemyType::PLAYERMUMMY, x, y);
	_vEnemy.push_back(PlayerMummy);
}

void EnemyManager::EnemyRemove()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();)
	{
		if ((*_viEnemy)->getDie())
		{
			_vEnemy.erase(_viEnemy);
			break;
		}
		else
		{
			++_viEnemy;
		}
	}
}


void EnemyManager::Collision()
{
	RECT temp;
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		for (int i = 0;i < _worldObjects->get_vTrap().size();++i)
		{
			if (IntersectRect(&temp, &(*_viEnemy)->getRect(), &_worldObjects->get_vTrap()[i].rc))
			{
				(*_viEnemy)->setTurn();
				(*_viEnemy)->setWall();
			}
			for (int i = 0;i < _enemyBullet->getVBullet().size();i++)
			{
				if ((IntersectRect(&temp, &(*_viEnemy)->getAttackRect(), &_ericRect)) || (IntersectRect(&temp, &_enemyBullet->getVBullet()[i].rect, &_ericRect)))
				{
					if (!_enemyBullet->getVBullet()[i].isFire)continue;
					_enemyBullet->removeBullet(i);
					if (!_playerManager->getEric()->getHit())
					{
						_playerManager->getEric()->setHit();
						_playerManager->getEric()->setEricHit();
					}
					break;
				}
				if ((IntersectRect(&temp, &(*_viEnemy)->getAttackRect(), &_baleogRect)) || (IntersectRect(&temp, &_enemyBullet->getVBullet()[i].rect, &_baleogRect)))
				{
					if (!_enemyBullet->getVBullet()[i].isFire)continue;
					_enemyBullet->removeBullet(i);
					_playerManager->getbaleog()->setBaleogHit();
				}
				if ((IntersectRect(&temp, &(*_viEnemy)->getAttackRect(), &_olafRect)) || (IntersectRect(&temp, &_enemyBullet->getVBullet()[i].rect, &_olafRect)))
				{
					if (!_enemyBullet->getVBullet()[i].isFire)continue;
					_enemyBullet->removeBullet(i);
				}
			}
		}
	}
}

void EnemyManager::bulletFire()
{

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{

		if ((*_viEnemy)->getisFire())
		{
			(*_viEnemy)->setisFire(false);
			_enemyBullet->bulletFire((*_viEnemy)->getX(), (*_viEnemy)->getY() - (*_viEnemy)->getImage()->getFrameHeight() / 2, getAngle((*_viEnemy)->getX(), (*_viEnemy)->getY() - (*_viEnemy)->getImage()->getFrameHeight() / 2, _playerManager->getPlayerEric().x, _playerManager->getPlayerEric().y));
			break;
		}
	}
}
