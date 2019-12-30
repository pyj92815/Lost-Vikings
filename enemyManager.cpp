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
	//적을 생성하는 함수
	enemyCreate();

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

void EnemyManager::enemyCreate()
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
	Mummy_3->init(EnemyType::MUMMY, 3179, 185);
	_vEnemy.push_back(Mummy_3);

	Enemy* Mummy_4;
	Mummy_4 = new Enemy_Mummy;
	Mummy_4->init(EnemyType::MUMMY, 3697, 955);
	_vEnemy.push_back(Mummy_4);

	Enemy* Mummy_5;
	Mummy_5 = new Enemy_Mummy;
	Mummy_5->init(EnemyType::MUMMY, 3340, 1240);
	_vEnemy.push_back(Mummy_5);

	Enemy* Scorpion_1;
	Scorpion_1 = new Enemy_Scorpion;
	Scorpion_1->init(EnemyType::SCORPION, 1440, 375);
	_vEnemy.push_back(Scorpion_1);

	Enemy* Scorpion_2;
	Scorpion_2 = new Enemy_Scorpion;
	Scorpion_2->init(EnemyType::SCORPION, 2063, 950);
	_vEnemy.push_back(Scorpion_2);

	Enemy* Scorpion_3;
	Scorpion_3 = new Enemy_Scorpion;
	Scorpion_3->init(EnemyType::SCORPION, 3246, 1245);
	_vEnemy.push_back(Scorpion_3);
	
	Enemy* Snake_1;
	Snake_1 = new Enemy_Snake;
	Snake_1->init(EnemyType::SNAKE, 1059, 380);
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


