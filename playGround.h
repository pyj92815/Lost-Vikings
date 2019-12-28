#pragma once
#include "gameNode.h"
#include "selectScene.h"
#include "worldMap.h"
#include "scene_Manager.h"
#include "playerManager.h" // 플레이어


class playGround : public gameNode
{
private:
	worldMap* _wd;
	scene_Manager* _sm;
	playerManager* _pm;   // 플레이어 매니져 

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용 함수
	virtual void render();	//그리기 전용 함수

};

