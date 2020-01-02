#pragma once
#include "gameNode.h"
//������Ʈ�� �÷��̾�� �浹�� ���� playerManager ���� ����
class playerManager;
enum tagTypeItem
{
	ITEM_BOMB,
	ITEM_TOMATO,
	ITEM_REDKEY,
	ITEM_REDLOCKER,
	ITEM_BLUEKEY,
	ITEM_BLUELOCKER,
};
enum tagTypeTrap
{
	TRAP_POISION,
	TRAP_NIDDLE,
	TRAP_WALL,
	TRAP_BORAD,
};
struct tagObjects
{
	tagTypeItem item;
	tagTypeTrap trap;
	RECT rc;				//������Ʈ(����/�� ��� ��)
	image* image;
	bool isCollision;		//������ �÷��̾ �������� �ƴ���
	float x, y;				//������Ʈ ��ǥ
	//������ x,y ��
	int frameX;
	int frameY;
	int maxFrameX;			//�ִ� �����Ӱ�
};
struct tagItem
{
	tagObjects oneBoom;
	tagObjects twoBoom;
	tagObjects oneTomato;
	tagObjects twoTomato;
	tagObjects blueKey;
	tagObjects blueLocker;
	tagObjects redKey;
	tagObjects redLocker;
};
class worldObjects : public gameNode
{
private:
	playerManager* _pm;
private:
	//���������������� ���͡����������������������
	vector<tagObjects>				 _vTrap;   // ���� , ��, ���� 
	vector<tagObjects>::iterator    _viTrap;
	//����������������� ���͡����������������������
	vector<tagItem>				  _vItem;
	vector<tagItem>::iterator	 _viItem;
private:
	//�����������ᰡ�� ���������������������������
	tagObjects _niddle[3];
private:
	//�����������ᵶ ���������������������������
	tagObjects _poision[4];
	bool _isntColliToNiddle;
private:
	//�����������Ắ �� ���ǡ����������������������
	tagObjects _flyingBoard; // ���� 
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
	tagItem _Items;
private:
	int _frameCount;
public:
	worldObjects();
	~worldObjects();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	vector<tagObjects> get_vTrap()			  { return _vTrap;}
	vector<tagObjects>::iterator get_viTrap()  { return _viTrap;}
	
	vector<tagItem> get_vItem()			  { return _vItem;}
	vector<tagItem>::iterator get_viItem() { return _viItem;}
	void setCollision(int arrNum) 
	{ 
		_vTrap[arrNum].isCollision = true; 
	}
	virtual void framework();
	virtual void move();
	bool getUpDown() { return _isUpDown; }
	void setPlayerManagerAddressLink(playerManager* pm) { _pm = pm; }


};

