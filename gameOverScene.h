#pragma once
#include "gameNode.h"

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

	void setting_Image();		// 필요한 이미지를 세팅한다.
	void setting_Pos();			// 위치 세팅을 한다.
	void letsGo_Ship();			// 배는 이동한다.
};


