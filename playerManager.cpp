#include "stdafx.h"
#include "playerManager.h"
#include "worldObjects.h"
#include "EnemyManager.h"



HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // 약 

	_baleog = new playerbaleog;
	_baleog->init(100, 185);

	_olaf = new PlayerOlaf;
	_olaf->init(180, 155);

	for (int i = 0;i < 3;i++)
	{
		_itemCount[i] = 0;
		_direction[i] = 0;
	}
	_trade = false;
	return S_OK;
}

void playerManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_eric->setItemKey();
		_baleog->setItemKey();
		_olaf->setItemKey();
	}
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
	if (_eric->getItem())
	{
		itemKey();
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		itemUse();
	}
	trapColision();
	itemColision();
	enemyColision();
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
	if (!_trade)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_direction[_playing] == 2 || _direction[_playing] == 3) _direction[_playing] -= 2;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_direction[_playing] == 0 || _direction[_playing] == 1) _direction[_playing] += 2;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_direction[_playing] == 1 || _direction[_playing] == 3) _direction[_playing] -= 1;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_direction[_playing] == 0 || _direction[_playing] == 2) _direction[_playing] += 1;
		}
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_trade ? _trade = false : _trade = true;
			for (int i = 0; i < _vInven.size(); ++i)
			{
				if (0 > _vInven.size()) break;
				if (_vInven[i].player == _playing && _vInven[i].invenNumber == _direction[_playing])
				{
					_vInven[i].choice = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < _vInven.size(); ++i)
		{
			if (0 > _vInven.size()) break;
			if (_vInven[i].choice)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
				{
					if (_vInven[i].player > 0) _vInven[i].player--;
				}
				if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
				{
					if (_vInven[i].player < 3)_vInven[i].player++;
				}
				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					_trade ? _trade = false : _trade = true;
					_vInven[i].choice = false;
					if (_vInven[i].player == 3)
					{
						this->removeInven(i);
					}
				}
			}
			else
			{
				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					_trade ? _trade = false : _trade = true;
				}
			}
		}
	}
}

void playerManager::itemUse()
{
	for (int i = 0; i < _vInven.size(); ++i)
	{
		if (0 > _vInven.size()) break;
		if (_vInven[i].player == _playing && _vInven[i].invenNumber == _direction[_playing])
		{
			switch (_vInven[i].typeItem)
			{
			case ITEM_BOMB:

				break;
			case ITEM_TOMATO:
				if (_playing == 0)
				{
					_eric->setEricHP();
				}
				else if (_playing == 1)
				{

				}
				else if (_playing == 2)
				{

				}
				this->removeInven(i);
				break;
			case ITEM_REDKEY:
				RECT temp;
				for (int j = 0; j < _wo->get_vItem().size(); ++j)
				{
					if (IntersectRect(&temp, &_eric->getEricRect(), &_wo->get_vItem()[j].rc))
					{
						if (_wo->get_vItem()[j].item == ITEM_REDLOCKER)
						{
							for (int k = 0; k < _wo->get_vTrap().size(); ++k)
							{
								if (_wo->get_vTrap()[k].trap == TRAP_RED_UNBREAKABLE_WALL)
								{
									_wo->setTrapCollision(k);
									this->removeInven(i);
								}
							}
						}
					}
				}	
				break;
			case ITEM_REDLOCKER:
				break;
			case ITEM_BLUEKEY:
				RECT temp2;
				for (int j = 0; j < _wo->get_vItem().size(); ++j)
				{
					if (IntersectRect(&temp2, &_eric->getEricRect(), &_wo->get_vItem()[j].rc))
					{
						if (_wo->get_vItem()[j].item == ITEM_BLUELOCKER)
						{
							for (int k = 0; k < _wo->get_vTrap().size(); ++k)
							{
								if (_wo->get_vTrap()[k].trap == TRAP_BLUE_UNBREAKABLE_WALL)
								{
									_wo->setTrapCollision(k);
									this->removeInven(i);
								}
							}
						}
					}
				}
				break;
			case ITEM_BLUELOCKER:
				break;
			}
			break;
		}
	}
}

void playerManager::trapColision() // 함정과 충돌 시
{
	for (int i = 0; i < _wo->get_vTrap().size(); ++i)
	{
		if (0 > _wo->get_vTrap().size()) break;
		RECT temp;

		// 에릭과 함정 충돌처리
		if (IntersectRect(&temp, &_eric->getEricRect(), &_wo->get_vTrap()[i].rc))
		{
			if (!_wo->get_vTrap()[i].isCollision)
			{
				if (_wo->get_vTrap()[i].trap == TRAP_POISION)
				{
					_eric->setEricState(STATE_POISON);
					_eric->setEricFrame();
					_wo->setTrapCollision(i);
					_eric->setEricStop();
					break;
				}
				else if (_wo->get_vTrap()[i].trap == TRAP_NIDDLE)
				{
					_eric->setEricState(STATE_TRAPDIE);
					_eric->setEricFrame();
					_eric->setEricFrameSpeed(25);
					_wo->setTrapCollision(i);
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

						if (_eric->getEric().state != STATE_PRESSDIE) _eric->setEricY(_wo->get_vTrap()[i].rc.bottom);
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
					else if ((_eric->getEric().rc.right >= _wo->get_vTrap()[i].rc.left+10 &&
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
						_wo->setTrapCollision(i);
					}
					else if (!_wo->get_vTrap()[i].isCollision && _eric->getEric().state == STATE_MOVE)
					{
						_eric->setEricState(STATE_PUSH);
						_eric->setEricFrame();
						_eric->setEricX(_wo->get_vTrap()[i].x - _eric->getEric().image->getFrameWidth() - 5);
					}
					else if (!_wo->get_vTrap()[i].isCollision && _eric->getEric().state == STATE_ERIC_JUMP)
					{
						_eric->setEricX(_wo->get_vTrap()[i].x - _eric->getEric().image->getFrameWidth() - 5);
					}
					else
					{
						_eric->setEricX(_wo->get_vTrap()[i].x - _eric->getEric().image->getFrameWidth() - 5);
					}

				}
				else if (_wo->get_vTrap()[i].trap == TRAP_RED_UNBREAKABLE_WALL ||
					_wo->get_vTrap()[i].trap == TRAP_BLUE_UNBREAKABLE_WALL)
				{
					if (!_wo->get_vTrap()[i].isCollision && _eric->getEric().state == STATE_MOVE)
					{
						_eric->setEricState(STATE_PUSH);
						_eric->setEricFrame();
					}
						_eric->setEricX(_wo->get_vTrap()[i].x - _eric->getEric().image->getFrameWidth() - 5);
				}
			}
		}
	}

	///=========================
	//발레오그 충돌
	for (int i = 0; i < _wo->get_vTrap().size(); ++i)
	{
		if (0 > _wo->get_vTrap().size()) break;
		RECT temp;
		if (IntersectRect(&temp, &_baleog->getBaleogRect(), &_wo->get_vTrap()[i].rc))
		{
			if (!_wo->get_vTrap()[i].isCollision)
			{
				if (_wo->get_vTrap()[i].trap == TRAP_POISION)
				{
					_baleog->setBaleogState(STATE_POISON);
					_baleog->setBaleogFrame();
					_wo->setTrapCollision(i);
					_baleog->setBaleogStop();
					break;
				}
				else if (_wo->get_vTrap()[i].trap == TRAP_NIDDLE)
				{
					_baleog->setBaleogState(STATE_TRAPDIE);
					_baleog->setBaleogFrame();
					_baleog->setBaleogFrameSpeed(25);
					_wo->setTrapCollision(i);
					_baleog->setBaleogStop();
					break;
				}
				else if (_wo->get_vTrap()[i].trap == TRAP_BORAD)
				{
					if ((_baleog->getBaleog().rc.right >= _wo->get_vTrap()[i].rc.left + 10 &&
						_baleog->getBaleog().rc.right <= _wo->get_vTrap()[i].rc.right - 10 &&
						_baleog->getBaleog().rc.bottom >= _wo->get_vTrap()[i].rc.bottom) ||
						(_baleog->getBaleog().rc.left >= _wo->get_vTrap()[i].rc.left + 10 &&
							_baleog->getBaleog().rc.left <= _wo->get_vTrap()[i].rc.right - 10 &&
							_baleog->getBaleog().rc.bottom >= _wo->get_vTrap()[i].rc.bottom))
					{

						if (_baleog->getBaleog().state != STATE_PRESSDIE) _baleog->setBaleogY(_wo->get_vTrap()[i].rc.bottom);
						if (_baleog->getBaleog().posState == POSSTATE_GROUND)
						{
							if (_baleog->getBaleog().state != STATE_PRESSDIE)
							{
								_baleog->setBaleogState(STATE_PRESSDIE);
								_baleog->setBaleogFrame();
								_baleog->setBaleogFrameSpeed(10);
								_baleog->setBaleogStop();
							}
						}
					}
					else if ((_baleog->getBaleog().rc.right >= _wo->get_vTrap()[i].rc.left + 10 &&
						_baleog->getBaleog().rc.right <= _wo->get_vTrap()[i].rc.right - 10)
						||
						(_baleog->getBaleog().rc.left >= _wo->get_vTrap()[i].rc.left + 10 &&
							_baleog->getBaleog().rc.left <= _wo->get_vTrap()[i].rc.right - 10))
					{
						if (_baleog->getBaleog().state != STATE_PRESSDIE)
						{
							_baleog->setBaleogPosState(POSSTATE_GROUND);

							if (_wo->getUpDown())
							{
								_baleog->setBaleogY(_wo->get_vTrap()[i].rc.top - _baleog->getBaleog().image->getFrameHeight() + 3);
							}
							else
							{
								_baleog->setBaleogY(_wo->get_vTrap()[i].rc.top - _baleog->getBaleog().image->getFrameHeight() + 7);
							}
						}
					}
				}

				else if (_wo->get_vTrap()[i].trap == TRAP_WALL)
				{

					
					if (!_wo->get_vTrap()[i].isCollision && _baleog->getBaleog().state == STATE_MOVE)
					{
						_baleog->setBaleogState(STATE_PUSH);
						_baleog->setBaleogFrame();
						_baleog->setBaleogX(_wo->get_vTrap()[i].x - _baleog->getBaleog().image->getFrameWidth() - 5);
					}
					
					else
					{
						_baleog->setBaleogX(_wo->get_vTrap()[i].x - _baleog->getBaleog().image->getFrameWidth() - 5);
					}

				}

			}
		}

		RECT temp2;
		if (IntersectRect(&temp2, &_olaf->GetOlafRC(), &_wo->get_vTrap()[i].rc))
		{
			if (!_wo->get_vTrap()[i].isCollision)
			{
				if (_wo->get_vTrap()[i].trap == TRAP_POISION)
				{
					_olaf->ResetAnimation2();
					_wo->setTrapCollision(i);
					_olaf->Set_OlafState(STATE_POISON);
					//_eric->setEricStop();
					break;
				}
				else if (_wo->get_vTrap()[i].trap == TRAP_NIDDLE)
				{
					_olaf->ResetAnimation2();
					_wo->setTrapCollision(i);
					_olaf->Set_OlafState(STATE_TRAPDIE);
					//_eric->setEricStop();
					break;
				}
			}
		}
	}

}

void playerManager::itemColision()
{
	for (int i = 0; i < _wo->get_vItem().size(); ++i)
	{
		if (0 > _wo->get_vItem().size()) break;
		RECT temp;
		if (IntersectRect(&temp, &_eric->getEricRect(), &_wo->get_vItem()[i].rc))
		{
			if (_wo->get_vItem()[i].item == ITEM_BLUELOCKER ||
				_wo->get_vItem()[i].item == ITEM_REDLOCKER) continue;
			if (!_wo->get_vItem()[i].isCollision)
			{
				tagInven inven;
				inven.image = _wo->get_vItem()[i].image;
				inven.typeItem = _wo->get_vItem()[i].item;
				inven.player = _playing;
				_itemCount[_playing] = 0;
				for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
				{
					if (_viInven->player == _playing) _itemCount[_playing]++;
				}
				inven.invenNumber = _itemCount[_playing]; // 순차적으로 아이템을 넣는다.
				if (_itemCount[_playing] < 4)
				{
					_vInven.push_back(inven);
					_wo->setItemCollision(i);
				}
				for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
				{
					cout << "=========================================================" << endl;
					cout << "인벤 image 높이 :" << _viInven->image->getHeight() << endl;
					cout << "플레이어 숫자 :" << _viInven->player << endl;
					cout << "아이템 넘버 :" << _viInven->invenNumber << endl;

				}
				break;
			}
		}
	}

	//=============================
	//발레오그 충돌

	for (int i = 0; i < _wo->get_vItem().size(); ++i)
	{
		if (0 > _wo->get_vItem().size()) break;
		RECT temp;
		if (IntersectRect(&temp, &_baleog->getBaleogRect(), &_wo->get_vItem()[i].rc))
		{
			if (_wo->get_vItem()[i].item == ITEM_BLUELOCKER ||
				_wo->get_vItem()[i].item == ITEM_REDLOCKER) continue;
			if (!_wo->get_vItem()[i].isCollision)
			{
				tagInven inven;
				inven.image = _wo->get_vItem()[i].image;
				inven.player = _playing;
				_itemCount[_playing] = 0;
				for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
				{
					if (_viInven->player == _playing) _itemCount[_playing]++;
				}
				inven.invenNumber = _itemCount[_playing]; // 순차적으로 아이템을 넣는다.
				if (_itemCount[_playing] < 4)
				{
					_vInven.push_back(inven);
					_wo->setItemCollision(i);
				}
				for (_viInven = _vInven.begin(); _viInven != _vInven.end(); ++_viInven)
				{
					cout << "=========================================================" << endl;
					cout << "인벤 image 높이 :" << _viInven->image->getHeight() << endl;
					cout << "플레이어 숫자 :" << _viInven->player << endl;
					cout << "아이템 넘버 :" << _viInven->invenNumber << endl;

				}
				break;
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

void playerManager::enemyColision()
{
	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{

		for (int j = 0; j < _baleog->getVArrow()->getVArrow().size(); j++)
		{
			/*if (0 > _arrow->getVArrow().size()) break;*/
			//충돌용 RECT
			RECT temp;

			//arrow와 enemy가 충돌했을 때(&temp,&arrow렉트
			if (IntersectRect(&temp, &_baleog->getVArrow()->getArrowRect(j), &_em->getVEnemy()[i]->getRect()))
			{
				//여기에 적 HP를 깍아줄 코드
				_baleog->getVArrow()->removeArrow(j);

				_em->getVEnemy()[i]->Hit();


				//충돌한 화살 삭제할 코드	
				break;
			}
		}
		// 에너미 vs 에릭 충돌
		RECT temp2;
		if (IntersectRect(&temp2, &_eric->getEricRect(), &_em->getVEnemy()[i]->getRect()))
		{
			if (_eric->getEric().state == STATE_ERIC_HEADBUTT && _eric->getEric().currentFrameX > 3)
			{
				_em->EnemyRemove(i);
				_eric->setEricState(STATE_ERIC_HEADBUTTEND);
				_eric->setEricFrame();
				_eric->setEricFrameSpeed(8);
				_eric->setEricUnable();
				break;
			}
		}


	}
}


