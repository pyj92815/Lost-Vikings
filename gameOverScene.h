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

struct tagReStart
{
	bool Re_Eric;
	bool Re_Baleog;
	bool Re_Olaf;
};

class gameOverScene : public gameNode
{
private:
	tagImagePos			_bg;
	tagImagePos			_ship;
	tagImagePos			_lightNing[3];
	tagImagePos			_goEric;
	tagImagePos			_goBaleog;
	tagImagePos			_goOlaf;
	tagImagePos			_goPlayer;
	RECT				_goPlayerRC[3];
	bool*				_goPLife;			// �÷��̾ �׾����� ��Ҵ����� ��Ƶд�.
	int					_goPCnt;			// ������ �� ġ�� �÷��̾ ��Ƴ���.
	tagReStart			_ReStartGame;
	bool				_PlayerRE[3];		// ���͸� ������ true�� ������ ���ϰ� �� �÷��̾ �츰��.

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


