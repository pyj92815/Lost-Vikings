#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "stageScene.h"


class scene_Manager : public gameNode
{	
	


public:
	scene_Manager();
	~scene_Manager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

