#include "stdafx.h"
#include "playerManager.h"
#include "worldObjects.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // 약 

	_baleog = new playerbaleog;
	_baleog->init(100, 185);

	_olaf = new PlayerOlaf;
	_olaf->init(180, 155);

	return S_OK;
}

void playerManager::update()
{
	KILLPlayer();	// 플레이어를 죽인다

	switch (_playing)
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

	_eric->update();
	_baleog->update();
	_olaf->update();

	trapColision();
	boradColision();
}

void playerManager::release()
{
	
	_eric->release();
	_baleog->release();
	_olaf->release();
}

void playerManager::render()
{
	_olaf->render();
	_baleog->render();
	_eric->render();
}

void playerManager::KILLPlayer()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		//_eric->player_Kill();
		_eric->setEricState(STATE_DIE);
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

void playerManager::itemKey()
{
	if (KEYMANAGER->isOnceKeyDown('E'))
	{

	}
}

void playerManager::trapColision()
{
	for (int i = 0; i < _wo->get_vTrap().size(); ++i)
	{
		if (0 > _wo->get_vTrap().size()) break;
		RECT temp;
		if (IntersectRect(&temp, &_eric->getEricRect(), &_wo->get_vTrap()[i].rc))
		{
			if (!_wo->get_vTrap()[i].isCollision)
			{
				if (_wo->get_vTrap()[i].trap == TRAP_POISION)
				{
					_eric->setEricState(STATE_POISON);
					_eric->setEricFrame();
					_wo->setCollision(i);
					_eric->setEricUnable();
					break;
				}
				else if (_wo->get_vTrap()[i].trap == TRAP_NIDDLE)
				{
					_eric->setEricState(STATE_TRAPDIE);
					_eric->setEricFrame();
					_eric->setEricFrameSpeed(25);
					_wo->setCollision(i);
					_eric->setEricUnable();
					break;
				}
			}
		}
	}
}

void playerManager::boradColision()
{
	for (int i = 0; i < _wo->get_vTrap().size(); ++i)
	{
		if (0 > _wo->get_vTrap().size()) break;
		if (_wo->get_vTrap()[i].trap == TRAP_BORAD)
		{
			if(_eric->getEric().rc.right >= _wo->get_vTrap()[i].rc.left &&
				_eric->getEric().x+)




		}	
	}
}
