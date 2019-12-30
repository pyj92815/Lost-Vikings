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
	_eric->update();
	_baleog->update();
	_olaf->update();
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

