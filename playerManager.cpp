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
					_eric->setEricStop();
					break;
				}
				else if (_wo->get_vTrap()[i].trap == TRAP_NIDDLE)
				{
					_eric->setEricState(STATE_TRAPDIE);
					_eric->setEricFrame();
					_eric->setEricFrameSpeed(25);
					_wo->setCollision(i);
					_eric->setEricStop();
					break;
				}
				else if (_wo->get_vTrap()[i].trap == TRAP_BORAD)
				{
					if ((_eric->getEric().rc.right >= _wo->get_vTrap()[i].rc.left + 10 &&
						_eric->getEric().rc.right <= _wo->get_vTrap()[i].rc.right - 10 &&
						_eric->getEric().rc.bottom >= _wo->get_vTrap()[i].rc.bottom) ||
						(_eric->getEric().rc.left >= _wo->get_vTrap()[i].rc.left + 10 &&
							_eric->getEric().rc.left <= _wo->get_vTrap()[i].rc.right - 10 &&
							_eric->getEric().rc.bottom >= _wo->get_vTrap()[i].rc.bottom))
					{
						
						if(_eric->getEric().state != STATE_PRESSDIE) _eric->setEricY(_wo->get_vTrap()[i].rc.bottom);
						if (_eric->getEric().posState == POSSTATE_GROUND)
						{
							if (_eric->getEric().state != STATE_PRESSDIE)
							{
								_eric->setEricState(STATE_PRESSDIE);
								_eric->setEricFrame();
								_eric->setEricFrameSpeed(10);
								_eric->setEricStop();
							}
						}
					}	
					else if((_eric->getEric().rc.right >= _wo->get_vTrap()[i].rc.left+10 &&
						  	_eric->getEric().rc.right <= _wo->get_vTrap()[i].rc.right-10  )
						   	||
						    (_eric->getEric().rc.left >= _wo->get_vTrap()[i].rc.left+10  &&
						   	_eric->getEric().rc.left <= _wo->get_vTrap()[i].rc.right-10 ))
					{
						if (_eric->getEric().state != STATE_PRESSDIE)
						{
							_eric->setEricPosState(POSSTATE_GROUND);
							_eric->setEricJump();
							_eric->setEricJumpPower();
							
							if (_wo->getUpDown())
							{
								_eric->setEricY(_wo->get_vTrap()[i].rc.top - _eric->getEric().image->getFrameHeight() + 3);
							}
							else
							{
								_eric->setEricY(_wo->get_vTrap()[i].rc.top - _eric->getEric().image->getFrameHeight() + 7);
							}
						}
					}
				}			
				
				else if (_wo->get_vTrap()[i].trap == TRAP_WALL)
				{
							
					if (_eric->getEric().state == STATE_ERIC_HEADBUTT && _eric->getEric().currentFrameX > 3)
					{
						_eric->setEricState(STATE_ERIC_HEADBUTTEND);
						_eric->setEricFrame();
						_eric->setEricFrameSpeed(8);
						_eric->setEricUnable();
						_wo->setCollision(i);
					}
					else if (!_wo->get_vTrap()[i].isCollision && _eric->getEric().state == STATE_MOVE)
					{
						_eric->setEricState(STATE_PUSH);
						_eric->setEricFrame();
						_eric->setEricX(_wo->get_vTrap()[i].x - _eric->getEric().image->getFrameWidth()-5);
					}
					else if (!_wo->get_vTrap()[i].isCollision && _eric->getEric().state == STATE_ERIC_JUMP)
					{
						_eric->setEricX(_wo->get_vTrap()[i].x - _eric->getEric().image->getFrameWidth()-5);
					}
					else
					{
						_eric->setEricX(_wo->get_vTrap()[i].x - _eric->getEric().image->getFrameWidth() - 5);
					}

				}

			}
		}
	}
}

void playerManager::itemColision()
{
	for (int i = 0; i < _wo->get_vItem().size(); i++)
	{
		if (0 > _wo->get_vItem().size()) break;
		RECT temp;
		if (IntersectRect(&temp, &_eric->getEricRect(), &_wo->get_vItem()[i].rc))
		{
			if (!_wo->get_vItem()[i].isCollision)
			{
				if (_wo->get_vItem()[i].item == ITEM_BOMB)
				{
					_wo->setCollision(i);
					break;
				}
			}
		}
	}
}


void playerManager::boradColision()
{
	/*for (int i = 0; i < _wo->get_vTrap().size(); ++i)
	{
		if (0 > _wo->get_vTrap().size()) break;
		if (_wo->get_vTrap()[i].trap == TRAP_BORAD)
		{
			if(_eric->getEric().rc.right >= _wo->get_vTrap()[i].rc.left &&
				_eric->getEric().x+)




		}
	}*/
}

