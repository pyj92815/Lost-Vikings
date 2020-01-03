#pragma once
#include "gameNode.h"

enum tagGOPlayer
{
	GOP_Eric,
	GOP_Baleog,
	GOP_Olaf
};

// 이미지 위치 정보
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
	bool*				_goPLife;			// 플레이어가 죽었는지 살았는지를 담아둔다.
	int					_goPCnt;			// 번개가 다 치면 플레이어가 살아난다.
	tagReStart			_ReStartGame;
	bool				_PlayerRE[3];		// 엔터를 누르면 true의 값으로 변하고 그 플레이어를 살린다.

public:
	gameOverScene();
	~gameOverScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setting_Image();		// 필요한 이미지를 세팅한다.
	void setting_Pos();			// 위치 세팅을 한다.
	void letsGo_Ship();			// 배는 이동한다.
	void restart_Select();		// 새로 시작할지 연산

};


