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

	void setting_Image();		// 필요한 이미지를 세팅한다.
	void setting_Pos();			// 위치 세팅을 한다.
	void letsGo_Ship();			// 배는 이동한다.
	void restart_Select();		// 새로 시작할지 연산

};


