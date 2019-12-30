#pragma once
#include"gameNode.h"
#include"Enemy_Mummy.h"
#include"Enemy_Scorpion.h"
#include"Enemy_Snake.h"
#include<vector>

using namespace std;
class EnemyManager: public gameNode
{
private:
	
private:
	//EnemyŬ���� ���ͷ� ����
	vector<Enemy*>			_vEnemy;
	vector<Enemy*>::iterator _viEnemy;

	//float _x, _y;
	

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void enemyCreate();
};

