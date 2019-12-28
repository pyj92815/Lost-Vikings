#pragma once
#include "gameNode.h"
#include "selectScene.h"
#include "worldMap.h"
#include "scene_Manager.h"
#include "playerManager.h" // �÷��̾�


class playGround : public gameNode
{
private:
	worldMap* _wd;
	scene_Manager* _sm;
	playerManager* _pm;   // �÷��̾� �Ŵ��� 

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();	//�׸��� ���� �Լ�

};

