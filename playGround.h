#pragma once
#include "gameNode.h"
#include "starScene.h"
#include "selectScene.h"
#include "worldMap.h"


class playGround : public gameNode
{
private:
	worldMap* _wd;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();	//�׸��� ���� �Լ�

};

