#pragma once
#include"singletonBase.h"
#include"Enemy.h"
#include<vector>

using namespace std;

class EnemyManager: public singletonBase<EnemyManager>
{
private:
	
private:
	//Enemy클래스 벡터로 선언
	//vector<Enemy>			_vEnemy;
	//vector<Enemy>::iterator _viEnemy;
	
	//float _x, _y;
	//RECT _rect;

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();

	void update();
	void render();

	void EnemySpawn(const char* EnemyImage, const char* Enemy_AttackImage, POINT position);
};

