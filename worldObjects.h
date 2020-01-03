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
	TRAP_RED_UNBREAKABLE_WALL,
	TRAP_BLUE_UNBREAKABLE_WALL,
	TRAP_BORAD,
};
struct tagObjects
{
	tagTypeItem item;
	tagTypeTrap trap;
	RECT rc;				//������Ʈ(����/�� ��� ��)
	image* image;
	bool isCollision;		//������ �÷��̾ �������� �ƴ���
	bool isKeyToOpen;		//�÷��̾ Ű�� ����ϸ� �ƴ���
	float x, y;				//������Ʈ ��ǥ
	//������ x,y ��
	int frameX;
	int frameY;
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
	vector<tagObjects>				  _vItem;
	vector<tagObjects>::iterator	 _viItem;
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
	tagObjects _Items[8];
	tagObjects _BOOM;
private:
	int _frameCount;			//������ ī����
	int _boomCount;				//��ź����� ��ź�� ������ī����
public:
	worldObjects();
	~worldObjects();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	vector<tagObjects> get_vTrap() { return _vTrap; }
	vector<tagObjects>::iterator get_viTrap() { return _viTrap; }

	vector<tagObjects> get_vItem() { return _vItem; }
	vector<tagObjects>::iterator get_viItem() { return _viItem; }

	void setTrapCollision(int arrNum){_vTrap[arrNum].isCollision = true;}
	void setItemCollision(int arrNum) { _vItem[arrNum].isCollision = true; }

	virtual void frameWork();
	virtual void move();
	bool getUpDown() { return _isUpDown; }
	void setPlayerManagerAddressLink(playerManager* pm) { _pm = pm; }

};

