#pragma once
#include "gameNode.h"
#include "Player.h"

#define GRAVITY 0.2f
#define PLAYER_SPEED 5

class PlayerOlaf : public gameNode
{
private:
	tagPlayer _olaf;
	int _olafStateTemp;
	int _olafPosStateTemp;
	int _currentLadderState;
	int _beforeLadderState;

	float _probeX_FixRange; // ��ٸ� Ż ��Ȳ�� �˻� ���� �� �����ϱ� ���� ����
	float _probeY_FixRange;
	bool _isShieldUp;

	RECT _shield;
	POINTFLOAT _shieldPos;
	POINTFLOAT _shieldRadius;

	COLORREF getPixel_BC;
	int r_BC;
	int g_BC;
	int b_BC;

	COLORREF getPixel_TC;
	int r_TC;
	int g_TC;
	int b_TC;

	RECT _ladderRect[9];
	int _selectedLadderIdx;
	bool _stopControl;
	bool _isItem;

public:
	PlayerOlaf();
	~PlayerOlaf();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void init_SettingOlafImg();
	void init_SetLadder();
	void UpdateFrame();
	void KeyControl();
	void SetOlafState();
	void SetOlafPosState();
	void PixelCollision();
	void ResetAnimation1();
	void ResetAnimation2();
	void ResetAnimation3();

	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _olaf.isDead = true; } // ���� ����
	RECT GetOlafRC() { return _olaf.rc; }
	bool GetOlafShieldState() { return _isShieldUp; }
	tagPlayer getOlaf() { return _olaf; }

	void setItemKey() { _isItem ? _isItem = false : _isItem = true; }
	void Set_OlafState(tagState state) { _olaf.state = state; }	// ���¸� ������ �ִ� ���� 

	void setOlafDead(bool dead) { _olaf.isDead = dead; }	// ���� �߰�
};