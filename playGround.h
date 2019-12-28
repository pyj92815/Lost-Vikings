#pragma once
#include "gameNode.h"
#include "selectScene.h"
#include "worldMap.h"
#include "playerManager.h" // �÷��̾�

class playGround : public gameNode
{
private:
	playerManager* _pm;   // �÷��̾� �Ŵ��� 
	worldMap* _wd;
	int a;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();	//�׸��� ���� �Լ�

};

