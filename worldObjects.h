#pragma once
#include "gameNode.h"

class playerManager;
enum tagType
{
	TYPE_BOMB,
	TYPE_TOMATO,
	TYPE_TOMATO2,
	TYPE_REDKEY,
	TYPE_REDLOCKER,
	TYPE_BLUEKEY,
	TYPE_BLUELOCKER,
};

struct tagObjects
{
	tagType itemType;
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
	//�����������Ắ �� ���ǡ����������������������
	tagObjects _flyingBoard;
	bool _isUpDown;
	tagObjects _breakableWallOne;
	tagObjects _breakableWallTwo;
	tagObjects _unbreakableWallOne;
	tagObjects _unbreakableWallTwo;
private:
	//���������������������������������������
	tagObjects _waterFall[3];
private:
	//����������������ۡ����������������������
	vector<tagObjects>				  _vItem;
	vector<tagObjects>::iterator	 _viItem;
	
	playerManager* _pm;
	/*tagObjects _Boom;
	tagObjects _redKey;
	tagObjects _redLocker;
	tagObjects _blueKey;
	tagObjects _blueLocker;
	tagObjects _tomato;*/

private:
	int _frameCount;
public:
	worldObjects();
	~worldObjects();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	vector<tagObjects> get_vItem() { return _vItem; }
	vector<tagObjects>::iterator get_viItem() { return _viItem; }

	virtual void framework();
	virtual void move();

	void setPlayerManagerAddressLink(playerManager* pm) { _pm = pm; }


};

