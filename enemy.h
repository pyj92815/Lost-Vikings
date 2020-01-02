#pragma once
#include"gameNode.h"



enum class EnemyState
{

	IDLE,		//ī�޶� �ۿ� ������ ������ �ִ� ����
	SCOUT,		//ī�޶� �ȿ� ���ͼ� �÷��̾ ã�� �����ϴ� ����
	DISCOVERY,	//�÷��̾ ���� ���� �ȿ� ���� �÷��̾ �����ϴ� ����
	ATTACK,		//�÷��̾ ���� ���� �ȿ� ���ͼ� �����ϴ� ����
	DIE			//HP�� 0���ϰ� �Ǿ� ����� ����
};

enum class EnemyLR
{
	LEFT,		//���� �̹��� ������ �����ϱ� ���� ENUM 
	RIGHT		//				"
};
enum class EnemyType
{
	MUMMY,
	SCORPION,
	SNAKE,
	PLAYERMUMMY,
};
class Enemy : public gameNode
{
protected:
	
	EnemyState _enemyState;					//���� ���� �� �̹��� ������ ������ ENUM��
	EnemyLR _enemyLR;						//					"
	EnemyType _enemyType;					//					"
	
	float _x, _y;							//���� ��ġ�� ������ ����
	RECT _enemyRect;						//���� ��Ʈ�� ������ ����
	RECT _enemyAttackRect;					//���� ���ݽ��� ��Ʈ
	RECT _enemy_DISCOVERY_Rect;				//���� Ž�� ����

	RECT _cameraRect;						//ī�޶��� ���� ī�޶� �ȿ� ���� ���Դ��� �Ǵ��ϱ� ����

	image* _image;							//���� �̹����� ������ ����

	int _probeX, _probeY;					//���� ��,�� �浹 ó���� ���� Ž�� ����
	int _turn_Num;							//���� ������ ��ȯ�ϱ� ���� ����

	int _frameX, _frameY;					//���� ������ ����
	int _frameCount;						//���� ������ ī��Ʈ ����

	
	bool _turn;								//���� ������ �ٲ��ֱ� ���� bool����
	bool _die;								//���� ��� ���¸� ��ȯ�ϱ� ���� �Լ�

	


public:
	RECT _ericRect;							//������ ��Ʈ
	RECT _olafRect;							//�ö����� ��Ʈ
	RECT _baleogRect;						//���α��� ��Ʈ
	RECT _playerRect;						//�÷����� ��Ʈ

	POINT _player;							//�÷��̾��� ��ġ	

	virtual HRESULT init(EnemyType enemyType, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void EnemyAction();				//���� ������ ���� �ൿ�� �����ϴ� �Լ�
	virtual void Frame();					//���� �������� �����ϴ� �Լ�

	virtual void Move();					//���� �������� ����ϴ� �Լ�
	virtual void Scout();					//���� Ž���� ����ϴ� �Լ�
	//���� ���¸� ��ȯ�ϴ� �Լ�(_enemyState)
	virtual EnemyState getEnemyState() { return _enemyState; }
	virtual RECT getRect() { return _enemyRect; }
	virtual bool getDie() { if(_die)return true; else return false; }

	virtual void setPlayerRect(RECT eric,RECT baleog,RECT olaf);

	//�̹��� �߰� �Լ�
	virtual void imageReset()
	{
		IMAGEMANAGER->addFrameImage("Enemy_Mummy", "./image./Enemy/Enemy_Mummy.bmp", 558, 180, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Mummy_Attack", "./image./Enemy/Enemy_Mummy_Attack.bmp", 540, 206, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Scorpion", "./image./Enemy/Enemy_Scorpion.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Scorpion_Attack", "./image./Enemy/Enemy_Scorpion_Attack.bmp", 784, 198, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Snake", "./image./Enemy/Enemy_Snake.bmp", 108, 24, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Snake_Attack", "./image./Enemy/Enemy_Snake_Attack", 780, 184, 6, 2, true, RGB(255, 0, 255));
	}
};

