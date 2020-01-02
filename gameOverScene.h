#pragma once
#include "gameNode.h"

// �̹��� ��ġ ����
struct tagImagePos
{
	image*				image;
	animation*			ani;
	RECT				rc;
	POINTFLOAT			pos;
	int					timer;
};

class gameOverScene : public gameNode
{
private:
	tagImagePos			_bg;
	tagImagePos			_ship;
	tagImagePos			_goEric;
	tagImagePos			_goBaleog;
	tagImagePos			_goOlaf;

public:
	gameOverScene();
	~gameOverScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setting_Image();		// �ʿ��� �̹����� �����Ѵ�.
	void setting_Pos();			// ��ġ ������ �Ѵ�.
	void letsGo_Ship();			// ��� �̵��Ѵ�.
};


