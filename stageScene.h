#pragma once
#include "gameNode.h"

// 플레이어의 타입
enum PlayerType
{
	PT_Run,
	PT_Attack,
	PT_Def
};

// 상태 UI의 정보를 담는 구조체
struct _tagStateUI
{
	POINTFLOAT		pos;						// 중점 
	RECT			rc;							// 렉트 좌표
	image*			image;						// 이미지 저장하는곳
	bool			dead;						// 캐릭터가 죽었는지 확인
};

class stageScene : public gameNode
{
private:
	_tagStateUI		_UI_State[3];				// 캐릭터마다 상태 이미지가 있다. 3칸
	_tagStateUI		_UI_Inventory[3][4];		// 캐릭터마다 인벤토리가 있다. 각각 4칸씩
	_tagStateUI		_UI_Garbage;				// 휴지통 이미지 위치
	int				_charNum;

public:
	stageScene();
	~stageScene();

	virtual HRESULT init();
	void release();
	void update();
	void render();

	void posSetting();
	void addStageImage();		// 스테이지 UI에 필요한 이미지를 추가하는 함수

	void testStateImage();		// 이미지 테스트용 함수

	void set_Player_Dead(int type, bool dead) { _UI_State[type].dead = dead; }	// 플레이어가 죽었는지 수정하는 함수

};

