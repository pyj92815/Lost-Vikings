#pragma once
#include "gameNode.h"

// �÷��̾��� Ÿ��
enum PlayerType
{
	PT_Run,
	PT_Attack,
	PT_Def
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
	int				_charNum;

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

	void set_Player_Dead(int type, bool dead) { _UI_State[type].dead = dead; }	// �÷��̾ �׾����� �����ϴ� �Լ�

};

