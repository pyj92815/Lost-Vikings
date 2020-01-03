#pragma once
#include"gameNode.h"
#include"Enemy_Mummy.h"
#include"Enemy_Scorpion.h"
#include"Enemy_Snake.h"
#include"Enemy_PlayerMummy.h"
#include"Enemy_Bullet.h"
#include<vector>
using namespace std;

class playerManager;

class EnemyManager : public gameNode
{
private:
	typedef vector<Enemy*>					vEnemy;
	typedef vector<Enemy*>::iterator		viEnemy; 
	typedef vector<Enemy_Bullet*>			vBullet;
	typedef vector<Enemy_Bullet*>::iterator viBullet;
private:
	//Enemy클래스 벡터로 선언
	vEnemy _vEnemy;
	viEnemy _viEnemy;
	vBullet _vBullet;
	viBullet _viBullet;
	

	playerManager* _playerManager;


public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyCreate();
	void EnemyCreate(float x, float y);
	void EnemyRemove();

	void Collision();
	void AddressLink(playerManager* pm) { _playerManager = pm; }
	
	void bulletFire();

	vector<Enemy*> getVEnemy() { return _vEnemy; }
	vector<Enemy*>::iterator getViEnemy() { return _viEnemy; }
};



