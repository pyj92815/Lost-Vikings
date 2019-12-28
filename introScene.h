#pragma once
#include "gameNode.h"

#define INTROIMAGESIZE 5		// ��Ʈ�� �̹��� ����
#define NEXTSCENECOUNT 50		// ���������� �Ѿ����� �����ִ� �ð�

enum Scene_Select_RC
{
	SS_GAME_START,
	SS_GAME_PASSWORD
};

struct tagIntroInfo
{
	image*			scene_Image;			// �̹��� ����
	int				scene_Number;			// �� �ѹ�
	bool			scene_State;			// �� ����
	int				fade_In;				// ���ķ����� ����
	char			scene_Str[20];			// ���ڿ� ���� ����
	int				scene_Cnt;				// �̹����� ��µǼ� �����ִ� �ð�

	RECT			scene_Select_rc[2];		// �� ���� ��Ʈ
	image*			scene_Select_Image;		// ���� �̹���
	bool			scene_Change_pos;		// �Է¿� ���� ���� �̹����� ��ǥ�� �ٲ۴�.
};

// ��Ʈ�� ���� ó���� Ŭ�����̴�.
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

	void addIntroImage();		// ��Ʈ�ο� ���� �̹����� �����Ѵ�.
	void setting_AlphaBlend();	// ���ĺ��忡 ����� ���� �����Ѵ�.
	void Select_Key();			// ���� Ű�� �����Ѵ�.

};

