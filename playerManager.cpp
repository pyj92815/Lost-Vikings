#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // �� 

	_baleog = new playerbaleog;
	_baleog->init(100, 185);

	_olaf = new PlayerOlaf;
	_olaf->init(180, 155);
	return S_OK;
}

void playerManager::update()
{
<<<<<<< HEAD

	_eric->update();
	_baleog->update();
	_olaf->update();

	switch (_P_type)
=======
	KILLPlayer();	// �÷��̾ ���δ�

	switch (_playing)
>>>>>>> fc585a4fce4e411f37c058052db62e3798d34b7f
	{
	case 0:
		_eric->set_stopKey(true);
		_baleog->set_stopKey(false);
		_olaf->set_stopKey(false);
		break;

	case 1:
		_eric->set_stopKey(false);
		_baleog->set_stopKey(true);
		_olaf->set_stopKey(false);
		break;

	case 2:
		_eric->set_stopKey(false);
		_baleog->set_stopKey(false);
		_olaf->set_stopKey(true);
		break;
	}

<<<<<<< HEAD
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		_P_type++;
		if (_P_type > 2)
		{
			_P_type = 0;
		}
	}

	//_eric->update();
	//_baleog->update();
	//_olaf->update();

	setColisionFloor();

=======
	_eric->update();
	_baleog->update();
	_olaf->update();
>>>>>>> fc585a4fce4e411f37c058052db62e3798d34b7f
}

void playerManager::release()
{
	
	_eric->release();
	_baleog->release();
	_olaf->release();
}

void playerManager::render()
{
	_eric->render();
	_baleog->render();
	_olaf->render();
}

<<<<<<< HEAD
void playerManager::setColisionFloor()
=======
void playerManager::KILLPlayer()
>>>>>>> fc585a4fce4e411f37c058052db62e3798d34b7f
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_eric->player_Kill();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_baleog->player_Kill();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_olaf->player_Kill();
	}
}

