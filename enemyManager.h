#pragma once
#include"gameNode.h"
#include"Enemy_Mummy.h"
#include"Enemy_Scorpion.h"
#include"Enemy_Snake.h"
#include"Enemy_PlayerMummy.h"
#include<vector>
using namespace std;

class playerManager;

class EnemyManager : public gameNode
{
private:

private:
	//EnemyŬ���� ���ͷ� ����
	vector<Enemy*>			_vEnemy;
	vector<Enemy*>::iterator _viEnemy;

	playerManager* _playerManager;


public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyCreate();
	void EnemyCreate(float x,float y);
	void EnemyRemove();
	
	playerManager* getPlayerManager() { return _playerManager; }
};

