#pragma once
#include "gameNode.h"
#include "player.h"
#include <vector>
#define PI 3.141592654
#define BALEOG_SPEED 5



enum ARROWSTATE
{
	SHOT,
	FIRE_SHOT
};
struct tagArrow
{
	image* arrowImage;				//ȭ�� �̹��� ����
	RECT rc;						//ȭ�� ��Ʈ
	float x, y;						//ȭ�� ��ǥ
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	bool isFire;
	int count;
	int direction;
};

class arrow : public gameNode				//ȭ�� Ŭ����
{
private:
	vector<tagArrow> _vArrow;				//ȭ�� ���� ����
	vector<tagArrow>::iterator _viArrow;	//���ͷ�����
	float _range;							//��Ÿ�
	int _arrowMax;							//�ִ� ����
	int _direction;							//����
	ARROWSTATE _arrowState;					//ȭ�� ����

public:
	arrow() {};
	~arrow() {};
	virtual HRESULT init(int arrowMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float speed, float angle, int direction);
	void removeArrow(int arrNum);
	void arrowMove(bool fire);

	vector<tagArrow> getVArrow() { return _vArrow; }
	vector<tagArrow>::iterator getViArrow() { return _viArrow; }


};

class playerbaleog : public player	//���α� Ŭ����
{

private:
	tagPlayer _baleog;				//�÷��̾� �±�			
	bool _baleogAttackMotion;		//�Ұ��� ������ Į����2, ������ Į����1�� ���´�.
	bool _pullString;				//Ȱ������ ������ �� �����ϴ� �Ұ�
	bool _notMove;					//������ �� �� �̵��� �����ϰ� �ϴ� �Ұ�			

	float _probeY;
	float _moveSpeed;

	arrow* _ar;						//ȭ�� Ŭ������ �����ͷ� ����Ų��

	bool _stopControl;		// �̰��� true��� ������ �� ����.


	COLORREF getPixel_BC;
	int r_BC;
	int g_BC;
	int b_BC;

	COLORREF getPixel_TC;
	int r_TC;
	int g_TC;
	int b_TC;

	RECT _testRect;



public:
	playerbaleog();
	~playerbaleog();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void key();									//����Ű �Լ�
	void setBaleogState();						//���¿� �̹��� ã���ִ� �Լ�
	void PixelCollision();						//�ȼ� �浹 �Լ�
	void SetBaleogPosState();					//ū���� ���¿� �̹��� ã���ִ� �Լ�

	void baleogDie();


	tagPlayer getBaleog() { return _baleog; }

	void hgKey();	// �����̰� ���� ��� �̵�Ű
	void set_stopKey(bool stop) { _stopControl = stop; }
	void player_Kill() { _baleog.isDead = true; }

	//void PixelCollision();			// Y�� �浹 ó�� 
	void PixelRightCollision();		// X�� ������ �浹 ó�� 
	void PixelLeftCollision();		// X�� ����   �浹 ó�� 
};



