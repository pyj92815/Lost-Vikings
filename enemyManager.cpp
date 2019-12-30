#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	
	/*for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->init();
		
	}*/
	/*Enemy* Mummy;
	Mummy = new Enemy_Mummy;
	Mummy->init(EnemyType::MUMMY,83, 750);
	_vEnemy.push_back(Mummy);*/

	/*Enemy* Scorpion;
	Scorpion = new Enemy_Scorpion;
	Scorpion->init(EnemyType::SCORPION, 83, 750);
	_vEnemy.push_back(Scorpion);*/

	Enemy* Snake;
	Snake = new Enemy_Snake;
	Snake->init(EnemyType::SNAKE, 83, 750);
	_vEnemy.push_back(Snake);

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
	}
}

void EnemyManager::render()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}


