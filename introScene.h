#pragma once
#include "gameNode.h"

#define INTROIMAGESIZE 5		// 인트로 이미지 개수
#define NEXTSCENECOUNT 50		// 다음씬으로 넘어가기까지 멈춰있는 시간

enum Scene_Select_RC
{
	SS_GAME_START,
	SS_GAME_PASSWORD
};

struct tagIntroInfo
{
	image*			scene_Image;			// 이미지 저장
	int				scene_Number;			// 씬 넘버
	bool			scene_State;			// 씬 상태
	int				fade_In;				// 알파랜더값 저장
	char			scene_Str[20];			// 문자열 저장 공간
	int				scene_Cnt;				// 이미지가 출력되서 멈춰있는 시간

	RECT			scene_Select_rc[2];		// 씬 선택 렉트
	image*			scene_Select_Image;		// 셀렉 이미지
	bool			scene_Change_pos;		// 입력에 따라 셀렉 이미지의 좌표를 바꾼다.
};

// 인트로 씬을 처리할 클래스이다.
class introScene : public gameNode
{
private:
	tagIntroInfo	_introScene;

public:
	introScene();
	~introScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addIntroImage();		// 인트로에 쓰일 이미지를 셋팅한다.
	void setting_AlphaBlend();	// 알파블렌드에 사용할 값을 연산한다.
	void Select_Key();			// 선택 키를 설정한다.

};

