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
	SNAKE
};
class Enemy : public gameNode
{
protected:
	//���� ���� �� �̹��� ������ ������ ENUM��
	EnemyState _enemyState;
	EnemyLR _enemyLR;
	EnemyType _enemyType;
	//���� ��ġ�� ������ ����
	float _x, _y;
	RECT _rect;
	image* _image;
	
	int _frameX,_frameY;
	int _frameCount;
public:
	
	virtual HRESULT init(EnemyType enemyType,float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void EnemyAction();
	virtual void EnemyCreate(float x, float y);

	//�̹��� �߰� �Լ�
	virtual void imageReset()
	{
		IMAGEMANAGER->addFrameImage("Enemy_Mummy", "./_Resources./_Enemy/Enemy_Mummy.bmp", 696, 224, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Mummy_Attack", "./_Resources./_Enemy/Enemy_Mummy_Attack.bmp", 672, 256, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Scorpion", "./_Resources./_Enemy/Enemy_Scorpion.bmp", 480, 240, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Scorpion_Attack", "./_Resources./_Enemy/Enemy_Scorpion_Attack.bmp", 980, 248, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Snake", "./_Resources./_Enemy/Enemy_Snake.bmp", 288, 16, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_Snake_Attack", "./_Resources./_Enemy/Enemy_Snake_Attack", 765, 120, 9, 2, true, RGB(255, 0, 255));
	}
};

