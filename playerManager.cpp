#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // ¾à 

	_baleog = new playerbaleog;
	_baleog->init(100, 185);

	_olaf = new PlayerOlaf;
	_olaf->init(180, 155);

	_P_type = 0;

	return S_OK;
}

void playerManager::update()
{
	_eric->update();
	_baleog->update();
	_olaf->update();
	switch (_P_type)
	{
	case ERIC:
		_eric->update();
		break;

	case BALEOG:
		_baleog->update();
		break;

	case OLAF:
		_olaf->update();
		break;
	}

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

