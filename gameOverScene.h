#pragma once
#include "gameNode.h"

enum tagGOPlayer
{
	GOP_Eric,
	GOP_Baleog,
	GOP_Olaf
};

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
	tagImagePos			_lightNing;
	tagImagePos			_goEric;
	tagImagePos			_goBaleog;
	tagImagePos			_goOlaf;
	tagImagePos			_goPlayer;
	RECT				_goPlayerRC[3];

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
	void restart_Select();		// ���� �������� ����

};


