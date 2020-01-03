#pragma once
#include "gameNode.h"
#include "worldMap.h"			// �������������� �ʿ��ϱ� ������ �̰����� �̵�
#include "playerManager.h"		// �������������� �ʿ��ϱ� ������ �̰����� �̵�
#include "enemyManager.h"		// �������������� �ʿ��ϱ� ������ �̰����� �̵�


// �÷��̾��� Ÿ��
enum PlayerType
{
	PT_ERIC,
	PT_BALEOG,
	PT_OLAF
};


enum tagGiveUp
{
	GU_CENTER,
	GU_YES,
	GU_NO
};


// ���� UI�� ������ ��� ����ü
struct _tagStateUI
{
	POINTFLOAT		pos;						// ���� 
	RECT			rc;							// ��Ʈ ��ǥ
	image*			image;						// �̹��� �����ϴ°�
	bool			dead;						// ĳ���Ͱ� �׾����� Ȯ��
};

class stageScene : public gameNode
{
private:
	_tagStateUI		_UI_State[3];				// ĳ���͸��� ���� �̹����� �ִ�. 3ĭ
	_tagStateUI		_UI_Inventory[3][4];		// ĳ���͸��� �κ��丮�� �ִ�. ���� 4ĭ��
	_tagStateUI		_UI_Garbage;				// ������ �̹��� ��ġ
	_tagStateUI		_UI_GiveUp[3];				// ���� UI�� ����
	_tagStateUI		_UI_HP[3];					// HP ����

	int				_charNum;					// ĳ���͸� ����Ű�� ��ȣ
	int				_banjjack;

	worldMap* _wm;
	playerManager* _pm;
	EnemyManager* _em;

public:
	stageScene();
	~stageScene();

	virtual HRESULT init();
	void release();
	void update();
	void render();

	void posSetting();
	void addStageImage();		// �������� UI�� �ʿ��� �̹����� �߰��ϴ� �Լ�

	void testStateImage();		// �̹��� �׽�Ʈ�� �Լ�

	void set_PlayerDead();

	void collisionMIX();		// ȥ���� �浹�Լ�

};

