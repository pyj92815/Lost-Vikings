#pragma once
#include "gameNode.h"

struct tagObjects
{
	RECT rc;				//������Ʈ(����/�� ��� ��)
	image* image;
	bool isCollision;		//������ �÷��̾ �������� �ƴ���
	//������ x,y ��
	int frameX;
	int frameY;
	int maxFrameX;			//�ִ� �����Ӱ�
};
class worldObjects : public gameNode
{
private:
	//�����������ᰡ�� ���������������������������
	tagObjects _niddle[3];
private:
	//�����������ᵶ ���������������������������
	tagObjects _poision[4];
	bool _isntColliToNiddle;
	int _poisionCount;
private:
	//��������������ǡ����������������������
	tagObjects _flyingBoard[1];
private:
	//���������������������������������������
	tagObjects _waterFall[3];
private:
	int _frameCount;
public:
	worldObjects();
	~worldObjects();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual void collision(int x, int y);

	virtual void framework();
	virtual void move();
};

